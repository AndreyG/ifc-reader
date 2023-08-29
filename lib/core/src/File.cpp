#include "ifc/File.h"
#include "ifc/Trait.h"

#include "ifc/Attribute.h"
#include "ifc/Chart.h"
#include "ifc/Declaration.h"
#include "ifc/Expression.h"
#include "ifc/SyntaxTree.h"
#include "ifc/Type.h"

#include <cassert>
#include <span>
#include <stdexcept>
#include <unordered_map>
#include <optional>

namespace ifc
{
    namespace
    {
        using FileSignature = std::array<std::byte, 4>;

        constexpr auto as_bytes(auto... values)
        {
            return std::array { static_cast<std::byte>(values)... };
        }

        constexpr FileSignature CANONICAL_FILE_SIGNATURE = as_bytes(0x54, 0x51, 0x45, 0x1A);
    }

    struct File::Impl
    {
    private:
        struct Structure
        {
            FileSignature signature;
            FileHeader header;
        };

        std::span<std::byte const> blob_;
        std::unordered_map<std::string_view, PartitionSummary const*> table_of_contents_;

        Structure const * structure() const
        {
            return reinterpret_cast<Structure const *>(blob_.data());
        }

        size_t calc_size() const
        {
            auto result = sizeof(Structure) + raw_count(header().string_table_size);
            const auto toc = table_of_contents();
            result += toc.size_bytes();
            for (const auto & partition : toc)
                result += partition.size_bytes();
            return result;
        }

        template<typename T>
        T const* get_pointer(ByteOffset offset) const
        {
            return reinterpret_cast<T const*>(get_raw_pointer(offset));
        }

    public:
        Impl(BlobView blob)
            : blob_(blob)
        {
            if (structure()->signature != CANONICAL_FILE_SIGNATURE)
                throw std::invalid_argument("corrupted file signature");

            if (calc_size() != blob_.size())
                throw std::runtime_error("corrupted file");

            for (auto const& partition : table_of_contents())
            {
                table_of_contents_.emplace(get_string(partition.name), &partition);
            }
        }

        FileHeader const & header() const
        {
            return structure()->header;
        }

        std::span<PartitionSummary const> table_of_contents() const
        {
            auto const & h = header();
            return { get_pointer<PartitionSummary>(h.toc), raw_count(h.partition_count) };
        }

        const char* get_string(TextOffset index) const
        {
            return get_pointer<char>(header().string_table_bytes) + static_cast<size_t>(index);
        }

        std::byte const* get_raw_pointer(ByteOffset offset) const
        {
            return blob_.data() + static_cast<std::underlying_type_t<ByteOffset>>(offset);
        }

        template<typename T, typename Index>
        std::optional<Partition<T, Index>> try_get_partition(std::string_view name) const
        {
            auto it = table_of_contents_.find(name);
            if (it == table_of_contents_.end())
                return std::nullopt;

            return get_partition<T, Index>(it->second);
        }

        template<typename T, typename Index>
        std::optional<Partition<T, Index>> try_get_partition() const
        {
            return try_get_partition<T, Index>(T::PartitionName);
        }

        template<typename T, typename Index>
        Partition<T, Index> get_partition(std::string_view name) const
        {
            return get_partition<T, Index>(table_of_contents_.at(name));
        }

        template<typename T, typename Index>
        Partition<T, Index> get_partition(PartitionSummary const * partition) const
        {
            assert(static_cast<size_t>(partition->entry_size) == sizeof(T));
            return { get_pointer<T>(partition->offset), raw_count(partition->cardinality) };
        }

        std::unordered_map<DeclIndex, std::vector<AttrIndex>> const & trait_declaration_attributes()
        {
            if (!trait_declaration_attributes_)
            {
                trait_declaration_attributes_.emplace();

                // ObjectTraits, FunctionTraits or Attributes for a template.
                // We could separate this trait & .msvc.trait.decl-attrs.
                // But the type is the same so it fits nicely here I think.
                fill_decl_attributes("trait.attribute");
                // All other attributes like [[nodiscard]] etc...
                fill_decl_attributes(".msvc.trait.decl-attrs");
            }
            return *trait_declaration_attributes_;
        }

        std::unordered_map<DeclIndex, TextOffset> const & trait_deprecation_texts()
        {
            if (!trait_deprecation_texts_)
            {
                trait_deprecation_texts_.emplace();

                if (auto deprecations = try_get_partition<AssociatedTrait<TextOffset>, Index>("trait.deprecated"))
                {
                    for (auto deprecation : *deprecations)
                    {
                        (*trait_deprecation_texts_)[deprecation.decl] = deprecation.trait;
                    }
                }
            }
            return *trait_deprecation_texts_;
        }

        std::unordered_map<DeclIndex, Sequence> const& trait_friendship_of_class()
        {
            if (!trait_friendship_of_class_)
            {
                trait_friendship_of_class_.emplace();

                if (auto friendships = try_get_partition<AssociatedTrait<Sequence>, Index>("trait.friend"))
                {
                    for (auto friendship : *friendships)
                    {
                        (*trait_friendship_of_class_)[friendship.decl] = friendship.trait;
                    }
                }
            }
            return *trait_friendship_of_class_;
        }

    private:
        void fill_decl_attributes(std::string_view partition)
        {
            if (auto attributes = try_get_partition<AssociatedTrait<AttrIndex>, Index>(partition))
            {
                for (auto attribute : *attributes)
                {
                    (*trait_declaration_attributes_)[attribute.decl].push_back(attribute.trait);
                }
            }
        }

        std::optional<std::unordered_map<DeclIndex, TextOffset>> trait_deprecation_texts_;
        std::optional<std::unordered_map<DeclIndex, std::vector<AttrIndex>>> trait_declaration_attributes_;
        std::optional<std::unordered_map<DeclIndex, Sequence>> trait_friendship_of_class_;
    };

    FileHeader const& File::header() const
    {
        return impl_->header();
    }

    std::span<PartitionSummary const> File::table_of_contents() const
    {
        return impl_->table_of_contents();
    }

    const char* File::get_string(TextOffset index) const
    {
        return impl_->get_string(index);
    }

    Sequence File::global_scope() const
    {
        return scope_descriptors()[header().global_scope];
    }

    ScopePartition File::scope_descriptors() const
    {
        return impl_->get_partition<Sequence, ScopeIndex>("scope.desc");
    }

    std::byte const* File::get_data_pointer(PartitionSummary const& partition) const
    {
        return impl_->get_raw_pointer(partition.offset);
    }

    Partition<Declaration, Index> File::declarations() const
    {
        return get_partition_with_cache<Declaration, Index>(cached_declarations_);
    }

#define DEFINE_PARTITION_GETTER(ElementType, IndexType, Property)                           \
    Partition<ElementType, IndexType> File::Property() const {                              \
        return get_partition_with_cache<ElementType, IndexType>(cached_ ## Property ## _);  \
    }

    // Declarations
    DEFINE_PARTITION_GETTER(ScopeDeclaration, DeclIndex, scope_declarations)
    DEFINE_PARTITION_GETTER(TemplateDeclaration, DeclIndex, template_declarations)
    DEFINE_PARTITION_GETTER(PartialSpecialization, DeclIndex, partial_specializations)
    DEFINE_PARTITION_GETTER(Specialization, DeclIndex, specializations)
    DEFINE_PARTITION_GETTER(UsingDeclaration, DeclIndex, using_declarations)
    DEFINE_PARTITION_GETTER(Enumeration, DeclIndex, enumerations)
    DEFINE_PARTITION_GETTER(Enumerator, DeclIndex, enumerators)
    DEFINE_PARTITION_GETTER(AliasDeclaration, DeclIndex, alias_declarations)
    DEFINE_PARTITION_GETTER(DeclReference, DeclIndex, decl_references)
    DEFINE_PARTITION_GETTER(FunctionDeclaration, DeclIndex, functions)
    DEFINE_PARTITION_GETTER(MethodDeclaration, DeclIndex, methods)
    DEFINE_PARTITION_GETTER(Constructor, DeclIndex, constructors)
    DEFINE_PARTITION_GETTER(Destructor, DeclIndex, destructors)
    DEFINE_PARTITION_GETTER(VariableDeclaration, DeclIndex, variables)
    DEFINE_PARTITION_GETTER(FieldDeclaration, DeclIndex, fields)
    DEFINE_PARTITION_GETTER(ParameterDeclaration, DeclIndex, parameters)
    DEFINE_PARTITION_GETTER(Concept, DeclIndex, concepts)
    DEFINE_PARTITION_GETTER(FriendDeclaration, DeclIndex, friends)
    DEFINE_PARTITION_GETTER(IntrinsicDeclaration, DeclIndex,  intrinsic_declarations)

    Partition<SpecializationForm, SpecFormIndex> File::specialization_forms() const
    {
        return get_partition_with_cache<SpecializationForm, SpecFormIndex>( cached_specialization_forms_);
    }

    // Types
    DEFINE_PARTITION_GETTER(FundamentalType, TypeIndex, fundamental_types)
    DEFINE_PARTITION_GETTER(DesignatedType, TypeIndex, designated_types)
    DEFINE_PARTITION_GETTER(TorType, TypeIndex, tor_types)
    DEFINE_PARTITION_GETTER(SyntacticType, TypeIndex, syntactic_types)
    DEFINE_PARTITION_GETTER(ExpansionType, TypeIndex, expansion_types)
    DEFINE_PARTITION_GETTER(PointerType, TypeIndex, pointer_types)
    DEFINE_PARTITION_GETTER(FunctionType, TypeIndex, function_types)
    DEFINE_PARTITION_GETTER(MethodType, TypeIndex, method_types)
    DEFINE_PARTITION_GETTER(ArrayType, TypeIndex, array_types)
    DEFINE_PARTITION_GETTER(BaseType, TypeIndex, base_types)
    DEFINE_PARTITION_GETTER(TupleType, TypeIndex, tuple_types)
    DEFINE_PARTITION_GETTER(LvalueReference, TypeIndex, lvalue_references)
    DEFINE_PARTITION_GETTER(RvalueReference, TypeIndex, rvalue_references)
    DEFINE_PARTITION_GETTER(QualifiedType, TypeIndex, qualified_types)
    DEFINE_PARTITION_GETTER(ForallType, TypeIndex, forall_types)
    DEFINE_PARTITION_GETTER(SyntaxType, TypeIndex, syntax_types)
    DEFINE_PARTITION_GETTER(PlaceholderType, TypeIndex, placeholder_types)
    DEFINE_PARTITION_GETTER(TypenameType, TypeIndex, typename_types)
    DEFINE_PARTITION_GETTER(DecltypeType,       TypeIndex, decltype_types)

    // Attributes
    DEFINE_PARTITION_GETTER(AttrBasic, AttrIndex, basic_attributes)
    DEFINE_PARTITION_GETTER(AttrScoped, AttrIndex, scoped_attributes)
    DEFINE_PARTITION_GETTER(AttrLabeled, AttrIndex, labeled_attributes)
    DEFINE_PARTITION_GETTER(AttrCalled, AttrIndex, called_attributes)
    DEFINE_PARTITION_GETTER(AttrExpanded, AttrIndex, expanded_attributes)
    DEFINE_PARTITION_GETTER(AttrFactored, AttrIndex, factored_attributes)
    DEFINE_PARTITION_GETTER(AttrElaborated, AttrIndex, elaborated_attributes)
    DEFINE_PARTITION_GETTER(AttrTuple, AttrIndex, tuple_attributes)

    // Expressions
    DEFINE_PARTITION_GETTER(LiteralExpression, ExprIndex, literal_expressions)
    DEFINE_PARTITION_GETTER(TypeExpression, ExprIndex, type_expressions)
    DEFINE_PARTITION_GETTER(NamedDecl, ExprIndex, decl_expressions)
    DEFINE_PARTITION_GETTER(UnqualifiedId, ExprIndex, unqualified_id_expressions)
    DEFINE_PARTITION_GETTER(TemplateId, ExprIndex, template_ids)
    DEFINE_PARTITION_GETTER(TemplateReference, ExprIndex, template_references)
    DEFINE_PARTITION_GETTER(MonadExpression, ExprIndex, monad_expressions)
    DEFINE_PARTITION_GETTER(DyadExpression, ExprIndex, dyad_expressions)
    DEFINE_PARTITION_GETTER(StringExpression, ExprIndex, string_expressions)
    DEFINE_PARTITION_GETTER(CallExpression, ExprIndex, call_expressions)
    DEFINE_PARTITION_GETTER(SizeofExpression, ExprIndex, sizeof_expressions)
    DEFINE_PARTITION_GETTER(AlignofExpression, ExprIndex, alignof_expressions)
    DEFINE_PARTITION_GETTER(RequiresExpression, ExprIndex, requires_expressions)
    DEFINE_PARTITION_GETTER(TupleExpression, ExprIndex, tuple_expressions)
    DEFINE_PARTITION_GETTER(PathExpression, ExprIndex, path_expressions)
    DEFINE_PARTITION_GETTER(ReadExpression, ExprIndex, read_expressions)
    DEFINE_PARTITION_GETTER(SyntaxTreeExpression, ExprIndex, syntax_tree_expressions)

    DEFINE_PARTITION_GETTER(ExpressionListExpression, ExprIndex, expression_lists)
    DEFINE_PARTITION_GETTER(QualifiedNameExpression, ExprIndex, qualified_name_expressions)
    DEFINE_PARTITION_GETTER(PackedTemplateArguments, ExprIndex, packed_template_arguments)
    DEFINE_PARTITION_GETTER(ProductValueTypeExpression, ExprIndex, product_value_type_expressions)

    Partition<StringLiteral, StringIndex> File::string_literal_expressions() const
    {
        return get_partition_with_cache<StringLiteral, StringIndex>(cached_string_literal_expressions_);
    }

    // Charts
    DEFINE_PARTITION_GETTER(ChartUnilevel,   ChartIndex, unilevel_charts)
    DEFINE_PARTITION_GETTER(ChartMultilevel, ChartIndex, multilevel_charts)

    // Literals
    DEFINE_PARTITION_GETTER(IntegerLiteral,  LitIndex,   integer_literals)
    DEFINE_PARTITION_GETTER(FPLiteral,       LitIndex,   fp_literals)
    
    // Syntax Trees
    DEFINE_PARTITION_GETTER(SimpleTypeSpecifier, SyntaxIndex, simple_type_specifiers)
    DEFINE_PARTITION_GETTER(DecltypeSpecifier, SyntaxIndex, decltype_specifiers)
    DEFINE_PARTITION_GETTER(TypeSpecifierSeq, SyntaxIndex, type_specifier_seq_syntax_trees)
    DEFINE_PARTITION_GETTER(DeclSpecifierSeq, SyntaxIndex, decl_specifier_seq_syntax_trees)
    DEFINE_PARTITION_GETTER(TypeIdSyntax, SyntaxIndex, typeid_syntax_trees)
    DEFINE_PARTITION_GETTER(DeclaratorSyntax, SyntaxIndex, declarator_syntax_trees)
    DEFINE_PARTITION_GETTER(PointerDeclaratorSyntax, SyntaxIndex, pointer_declarator_syntax_trees)
    DEFINE_PARTITION_GETTER(FunctionDeclaratorSyntax, SyntaxIndex, function_declarator_syntax_trees)
    DEFINE_PARTITION_GETTER(ParameterDeclaratorSyntax, SyntaxIndex, parameter_declarator_syntax_trees)
    DEFINE_PARTITION_GETTER(ExpressionSyntax, SyntaxIndex, expression_syntax_trees)
    DEFINE_PARTITION_GETTER(RequiresClauseSyntax, SyntaxIndex, requires_clause_syntax_trees)
    DEFINE_PARTITION_GETTER(SimpleRequirementSyntax, SyntaxIndex, simple_requirement_syntax_trees)
    DEFINE_PARTITION_GETTER(TypeRequirementSyntax, SyntaxIndex, type_requirement_syntax_trees)
    DEFINE_PARTITION_GETTER(NestedRequirementSyntax, SyntaxIndex, nested_requirement_syntax_trees)
    DEFINE_PARTITION_GETTER(CompoundRequirementSyntax, SyntaxIndex, compound_requirement_syntax_trees)
    DEFINE_PARTITION_GETTER(RequirementBodySyntax, SyntaxIndex, requirement_body_syntax_trees)
    DEFINE_PARTITION_GETTER(TypeTemplateArgumentSyntax, SyntaxIndex, type_template_argument_syntax_trees)
    DEFINE_PARTITION_GETTER(TemplateArgumentListSyntax, SyntaxIndex, template_argument_list_syntax_trees)
    DEFINE_PARTITION_GETTER(TemplateIdSyntax, SyntaxIndex, templateid_syntax_trees)
    DEFINE_PARTITION_GETTER(TypeTraitIntrinsicSyntax, SyntaxIndex, type_trait_intrinsic_syntax_trees)
    DEFINE_PARTITION_GETTER(TupleSyntax, SyntaxIndex, tuple_syntax_trees)

    // Names
    DEFINE_PARTITION_GETTER(OperatorFunctionName, NameIndex, operator_names)
    DEFINE_PARTITION_GETTER(SpecializationName,   NameIndex, specialization_names)
    DEFINE_PARTITION_GETTER(LiteralName,          NameIndex, literal_names)

#undef DEFINE_PARTITION_GETTER

    // Heaps
    Partition<TypeIndex, Index> File::type_heap() const
    {
        return get_partition_with_cache<TypeIndex, Index>(cached_type_heap_, "heap.type");
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return get_partition_with_cache<ExprIndex, Index>(cached_expr_heap_, "heap.expr");
    }

    Partition<AttrIndex, Index> File::attr_heap() const
    {
        return get_partition_with_cache<AttrIndex, Index>(cached_attr_heap_, "heap.attr");
    }

    Partition<SyntaxIndex, Index> File::syntax_heap() const
    {
        return get_partition_with_cache<SyntaxIndex, Index>(cached_syntax_heap_, "heap.syn");
    }

    // Module References
    Partition<ModuleReference, Index> File::imported_modules() const
    {
        return get_partition_with_cache<ModuleReference, Index>(cached_imported_modules_, "module.imported");
    }

    Partition<ModuleReference, Index> File::exported_modules() const
    {
        return get_partition_with_cache<ModuleReference, Index>(cached_exported_modules_, "module.exported");
    }

    // Deduction Guides
    Partition<DeclIndex> File::deduction_guides() const
    {
        return impl_->get_partition<DeclIndex, uint32_t>("name.guide");
    }

    template<typename RetType, typename Value>
    RetType get_value(DeclIndex declaration, std::unordered_map<DeclIndex, Value> const & map)
    {
        if (auto it = map.find(declaration); it != map.end())
            return it->second;

        return {};
    }

    TextOffset File::trait_deprecation_texts(DeclIndex declaration) const
    {
        return get_value<TextOffset>(declaration, impl_->trait_deprecation_texts());
    }

    std::span<AttrIndex const> File::trait_declaration_attributes(DeclIndex declaration) const
    {
        return get_value<std::span<AttrIndex const>>(declaration, impl_->trait_declaration_attributes());
    }

    Sequence File::trait_friendship_of_class(DeclIndex declaration) const
    {
        return get_value<Sequence>(declaration, impl_->trait_friendship_of_class());
    }

    template<typename T, typename Index>
    Partition<T, Index> File::get_partition_with_cache(std::optional<Partition<T, Index>> & cache) const
    {
        return get_partition_with_cache<T, Index>(cache, T::PartitionName);
    }

    template <typename T, typename Index>
    Partition<T, Index> File::get_partition_with_cache(std::optional<Partition<T, Index>>& cache, std::string_view name) const
    {
        if (cache.has_value())
            return *cache;
        auto result = impl_->get_partition<T, Index>(name);
        cache = result;
        return result;
    }

    File::File(BlobView data)
        : impl_(std::make_unique<Impl>(data))
    {
    }

    File::~File() = default;

    File::File           (File&&) noexcept = default;
    File& File::operator=(File&&) noexcept = default;

    ScopeDeclaration const& get_scope(File const& file, DeclIndex decl)
    {
        return file.scope_declarations()[decl];
    }

    Partition<Declaration, Index> get_declarations(File const& file, Sequence scope)
    {
        return file.declarations().slice(scope);
    }

    Partition<ExprIndex, Index> get_tuple_expression_elements(File const& file, TupleExpression const& tuple)
    {
        return file.expr_heap().slice(tuple.seq);
    }

    Partition<ExprIndex, Index> get_qualified_name_parts(File const& ifc, QualifiedNameExpression const& qualified_name_expression)
    {
        assert(qualified_name_expression.elements.sort() == ifc::ExprSort::Tuple);
        return get_tuple_expression_elements(ifc, ifc.tuple_expressions()[qualified_name_expression.elements]);
    }

    TypeBasis get_kind(ScopeDeclaration const & scope, File const & file)
    {
        return file.fundamental_types()[scope.type].basis;
    }
}
