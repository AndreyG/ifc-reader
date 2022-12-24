#include "ifc/File.h"
#include "ifc/Environment.h"
#include "ifc/Trait.h"

#include "ifc/Attribute.h"
#include "ifc/Chart.h"
#include "ifc/Declaration.h"
#include "ifc/Expression.h"
#include "ifc/SyntaxTree.h"
#include "ifc/Type.h"

#include <boost/iostreams/device/mapped_file.hpp>

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

        boost::iostreams::mapped_file_source fmap_;
        std::unordered_map<std::string_view, PartitionSummary const*> table_of_contents_;

        Structure const * structure() const
        {
            return reinterpret_cast<Structure const *>(fmap_.data());
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

        std::span<PartitionSummary const> table_of_contents() const
        {
            auto const & h = header();
            return { get_pointer<PartitionSummary>(h.toc), raw_count(h.partition_count) };
        }

        template<typename T>
        T const* get_pointer(ByteOffset offset) const
        {
            return static_cast<T const*>(get_raw_pointer(offset));
        }

        void const* get_raw_pointer(ByteOffset offset) const
        {
            return fmap_.data() + static_cast<size_t>(offset);
        }

    public:
        Impl(std::string const & path)
            : fmap_(path)
        {
            if (structure()->signature != CANONICAL_FILE_SIGNATURE)
                throw std::invalid_argument("corrupted file signature");

            if (calc_size() != fmap_.size())
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

        const char* get_string(TextOffset index) const
        {
            return get_pointer<char>(header().string_table_bytes) + static_cast<size_t>(index);
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

        template<typename T, typename Index>
        Partition<T, Index> get_partition() const
        {
            return get_partition<T, Index>(T::PartitionName);
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
    };

    FileHeader const& File::header() const
    {
        return impl_->header();
    }

    const char* File::get_string(TextOffset index) const
    {
        return impl_->get_string(index);
    }

    ScopeDescriptor File::global_scope() const
    {
        return scope_descriptors()[header().global_scope];
    }

    ScopePartition File::scope_descriptors() const
    {
        return impl_->get_partition<ScopeDescriptor, ScopeIndex>();
    }

    Partition<Declaration, Index> File::declarations() const
    {
        return get_partition_with_cache<Declaration, Index>(cached_declarations_);
    }

#define DEFINE_PARTITION_GETTER(ElementType, IndexType, Property)   \
    TypedPartition<ElementType, IndexType> File::Property() const { \
        return static_cast<TypedPartition<ElementType, IndexType>>( \
            get_partition_with_cache<ElementType, IndexType>(       \
                cached_ ## Property ## _)                           \
            );                                                      \
    }

#define DEFINE_DECL_PARTITION_GETTER(DeclType, DeclName) \
    DEFINE_PARTITION_GETTER(DeclType, DeclIndex, DeclName)

    DEFINE_DECL_PARTITION_GETTER(ScopeDeclaration,      scope_declarations)
    DEFINE_DECL_PARTITION_GETTER(TemplateDeclaration,   template_declarations)
    DEFINE_DECL_PARTITION_GETTER(UsingDeclaration,      using_declarations)
    DEFINE_DECL_PARTITION_GETTER(Enumeration,           enumerations)
    DEFINE_DECL_PARTITION_GETTER(Enumerator,            enumerators)
    DEFINE_DECL_PARTITION_GETTER(AliasDeclaration,      alias_declarations)
    DEFINE_DECL_PARTITION_GETTER(DeclReference,         decl_references)
    DEFINE_DECL_PARTITION_GETTER(FunctionDeclaration,   functions)
    DEFINE_DECL_PARTITION_GETTER(MethodDeclaration,     methods)
    DEFINE_DECL_PARTITION_GETTER(Constructor,           constructors)
    DEFINE_DECL_PARTITION_GETTER(Destructor,            destructors)
    DEFINE_DECL_PARTITION_GETTER(VariableDeclaration,   variables)
    DEFINE_DECL_PARTITION_GETTER(FieldDeclaration,      fields)
    DEFINE_DECL_PARTITION_GETTER(ParameterDeclaration,  parameters)
    DEFINE_DECL_PARTITION_GETTER(Concept,               concepts)
    DEFINE_DECL_PARTITION_GETTER(IntrinsicDeclaration,  intrinsic_declarations)

#undef DEFINE_DECL_PARTITION_GETTER

#define DEFINE_TYPE_PARTITION_GETTER(Type, TypeName) \
    DEFINE_PARTITION_GETTER(Type, TypeIndex, TypeName)

    DEFINE_TYPE_PARTITION_GETTER(FundamentalType,    fundamental_types)
    DEFINE_TYPE_PARTITION_GETTER(DesignatedType,     designated_types)
    DEFINE_TYPE_PARTITION_GETTER(TorType,            tor_types)
    DEFINE_TYPE_PARTITION_GETTER(SyntacticType,      syntactic_types)
    DEFINE_TYPE_PARTITION_GETTER(ExpansionType,      expansion_types)
    DEFINE_TYPE_PARTITION_GETTER(PointerType,        pointer_types)
    DEFINE_TYPE_PARTITION_GETTER(FunctionType,       function_types)
    DEFINE_TYPE_PARTITION_GETTER(MethodType,         method_types)
    DEFINE_TYPE_PARTITION_GETTER(BaseType,           base_types)
    DEFINE_TYPE_PARTITION_GETTER(TupleType,          tuple_types)
    DEFINE_TYPE_PARTITION_GETTER(LvalueReference,    lvalue_references)
    DEFINE_TYPE_PARTITION_GETTER(RvalueReference,    rvalue_references)
    DEFINE_TYPE_PARTITION_GETTER(QualifiedType,      qualified_types)
    DEFINE_TYPE_PARTITION_GETTER(ForallType,         forall_types)
    DEFINE_TYPE_PARTITION_GETTER(SyntaxType,         syntax_types)
    DEFINE_TYPE_PARTITION_GETTER(PlaceholderType,    placeholder_types)
    DEFINE_TYPE_PARTITION_GETTER(TypenameType,       typename_types)
    DEFINE_TYPE_PARTITION_GETTER(DecltypeType,       decltype_types)

#undef DEFINE_TYPE_PARTITION_GETTER

#define DEFINE_ATTR_PARTITION_GETTER(DeclType, DeclName) \
    DEFINE_PARTITION_GETTER(DeclType, AttrIndex, DeclName)

        DEFINE_ATTR_PARTITION_GETTER(AttrBasic, basic_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrScoped, scoped_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrLabeled, labeled_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrCalled, called_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrExpanded, expanded_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrFactored, factored_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrElaborated, elaborated_attributes)
        DEFINE_ATTR_PARTITION_GETTER(AttrTuple, tuple_attributes)

#undef DEFINE_ATTR_PARTITION_GETTER

#define DEFINE_EXPR_PARTITION_GETTER(ExprType, ExprName) \
    DEFINE_PARTITION_GETTER(ExprType, ExprIndex, ExprName)

    DEFINE_EXPR_PARTITION_GETTER(LiteralExpression, literal_expressions)
    DEFINE_EXPR_PARTITION_GETTER(TypeExpression,    type_expressions)
    DEFINE_EXPR_PARTITION_GETTER(NamedDecl,         decl_expressions)
    DEFINE_EXPR_PARTITION_GETTER(UnqualifiedId,     unqualified_id_expressions)
    DEFINE_EXPR_PARTITION_GETTER(TemplateId,        template_ids)
    DEFINE_EXPR_PARTITION_GETTER(MonadExpression,   monad_expressions)
    DEFINE_EXPR_PARTITION_GETTER(DyadExpression,    dyad_expressions)
    DEFINE_EXPR_PARTITION_GETTER(CallExpression,    call_expressions)
    DEFINE_EXPR_PARTITION_GETTER(SizeofExpression,  sizeof_expressions)
    DEFINE_EXPR_PARTITION_GETTER(AlignofExpression, alignof_expressions)
    DEFINE_EXPR_PARTITION_GETTER(RequiresExpression,requires_expressions)
    DEFINE_EXPR_PARTITION_GETTER(TupleExpression,   tuple_expressions)
    DEFINE_EXPR_PARTITION_GETTER(PathExpression,    path_expressions)
    DEFINE_EXPR_PARTITION_GETTER(ReadExpression,    read_expressions)
    DEFINE_EXPR_PARTITION_GETTER(SyntaxTreeExpression, syntax_tree_expressions)

    DEFINE_EXPR_PARTITION_GETTER(ExpressionListExpression,expression_lists)
    DEFINE_EXPR_PARTITION_GETTER(QualifiedNameExpression, qualified_name_expressions)
    DEFINE_EXPR_PARTITION_GETTER(PackedTemplateArguments, packed_template_arguments)
    DEFINE_EXPR_PARTITION_GETTER(ProductValueTypeExpression, product_value_type_expressions)

    Partition<StringLiteral, StringIndex> File::string_literal_expressions() const
    {
        return get_partition_with_cache<StringLiteral, StringIndex>(cached_string_literal_expressions_);
    }

#undef DEFINE_EXPR_PARTITION_GETTER

    DEFINE_PARTITION_GETTER(ChartUnilevel,   ChartIndex, unilevel_charts)
    DEFINE_PARTITION_GETTER(ChartMultilevel, ChartIndex, multilevel_charts)

    DEFINE_PARTITION_GETTER(IntegerLiteral,  LitIndex,   integer_literals)
    DEFINE_PARTITION_GETTER(FPLiteral,       LitIndex,   fp_literals)

#define DEFINE_SYNTAX_PARTITION_GETTER(SyntaxType, SyntaxName) \
    DEFINE_PARTITION_GETTER(SyntaxType, SyntaxIndex, SyntaxName)

    DEFINE_SYNTAX_PARTITION_GETTER(SimpleTypeSpecifier,         simple_type_specifiers)
    DEFINE_SYNTAX_PARTITION_GETTER(DecltypeSpecifier,           decltype_specifiers)
    DEFINE_SYNTAX_PARTITION_GETTER(TypeSpecifierSeq,            type_specifier_seq_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(DeclSpecifierSeq,            decl_specifier_seq_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TypeIdSyntax,                typeid_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(DeclaratorSyntax,            declarator_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(PointerDeclaratorSyntax,     pointer_declarator_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(FunctionDeclaratorSyntax,    function_declarator_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(ParameterDeclaratorSyntax,   parameter_declarator_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(ExpressionSyntax,            expression_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(RequiresClauseSyntax,        requires_clause_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(SimpleRequirementSyntax,     simple_requirement_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TypeRequirementSyntax,       type_requirement_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(NestedRequirementSyntax,     nested_requirement_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(CompoundRequirementSyntax,   compound_requirement_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(RequirementBodySyntax,       requirement_body_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TypeTemplateArgumentSyntax,  type_template_argument_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TemplateArgumentListSyntax,  template_argument_list_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TemplateIdSyntax,            templateid_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TypeTraitIntrinsicSyntax,    type_trait_intrinsic_syntax_trees)
    DEFINE_SYNTAX_PARTITION_GETTER(TupleSyntax,                 tuple_syntax_trees)

#undef DEFINE_SYNTAX_PARTITION_GETTER

    DEFINE_PARTITION_GETTER(OperatorFunctionName, NameIndex, operator_names)
    DEFINE_PARTITION_GETTER(SpecializationName,   NameIndex, specialization_names)
    DEFINE_PARTITION_GETTER(LiteralName,          NameIndex, literal_names)

#undef DEFINE_PARTITION_GETTER

    Partition<TypeIndex, Index> File::type_heap() const
    {
        return impl_->get_partition<TypeIndex, Index>("heap.type");
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return impl_->get_partition<ExprIndex, Index>("heap.expr");
    }

    Partition<AttrIndex, Index> File::attr_heap() const
    {
        return impl_->get_partition<AttrIndex, Index>("heap.attr");
    }

    Partition<SyntaxIndex, Index> File::syntax_heap() const
    {
        return impl_->get_partition<SyntaxIndex, Index>("heap.syn");
    }

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

    template<typename T, typename Index>
    Partition<T, Index> File::get_partition_with_cache(std::optional<Partition<T, Index>> & cache) const
    {
        if (cache.has_value())
            return *cache;
        auto result = impl_->get_partition<T, Index>();
        cache = result;
        return result;
    }

    File const& File::get_imported_module(ModuleReference module) const
    {
        if (auto owner = module.owner; is_null(owner))
        {
            // global module
            return env_->get_module_by_name(get_string(module.partition));
        }
        else
        {
            std::string name = get_string(owner);
            if (auto partition = module.partition; !is_null(partition))
                name.append(":").append(get_string(partition));
            return env_->get_module_by_name(name);
        }
    }

    File::File(std::string const & path, Environment* env)
        : env_(env)
        , impl_(std::make_unique<Impl>(path))
    {
    }

    File::~File() = default;

    File::File           (File&&) noexcept = default;
    File& File::operator=(File&&) noexcept = default;

    ScopeDeclaration const& get_scope(File const& file, DeclIndex decl)
    {
        return file.scope_declarations()[decl];
    }

    Partition<Declaration, Index> get_declarations(File const& file, ScopeDescriptor scope)
    {
        return file.declarations().slice(scope);
    }

    Partition<ExprIndex, Index> get_qualified_name_parts(File const& ifc, QualifiedNameExpression const& qualified_name_expression)
    {
        assert(qualified_name_expression.elements.sort() == ifc::ExprSort::Tuple);
        return ifc.expr_heap().slice(ifc.tuple_expressions()[qualified_name_expression.elements].seq);
    }

    TypeBasis get_kind(ScopeDeclaration const & scope, File const & file)
    {
        return file.fundamental_types()[scope.type].basis;
    }
}
