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

        template<typename T, typename Index>
        Partition<T, Index> get_and_cache_partition() const
        {
            return get_and_cache_partition<T, Index>(T::PartitionName);
        }

        template<typename T, typename Index>
        Partition<T, Index> get_and_cache_partition(std::string_view name) const
        {
            static Partition<T, Index> partition = try_get_partition<T, Index>(name)
                .value_or(Partition<T, Index>{nullptr, 0});
            return partition;
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

    // ------------------------------------------------------------------------

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

    // ------------------------------------------------------------------------

    Partition<Declaration, Index> File::declarations() const
    {
        return impl_->get_and_cache_partition<Declaration, Index>();
    }

    // ------------------------------------------------------------------------

    Partition<ScopeDeclaration, DeclIndex>      File::scope_declarations() const
    {
        return impl_->get_and_cache_partition<ScopeDeclaration, DeclIndex>();
    }

    Partition<TemplateDeclaration, DeclIndex>   File::template_declarations() const
    {
        return impl_->get_and_cache_partition<TemplateDeclaration, DeclIndex>();
    }

    Partition<PartialSpecialization, DeclIndex> File::partial_specializations() const
    {
        return impl_->get_and_cache_partition<PartialSpecialization, DeclIndex>();
    }

    Partition<Specialization, DeclIndex>        File::specializations() const
    {
        return impl_->get_and_cache_partition<Specialization, DeclIndex>();
    }

    Partition<UsingDeclaration, DeclIndex>      File::using_declarations() const
    {
        return impl_->get_and_cache_partition<UsingDeclaration, DeclIndex>();
    }

    Partition<Enumeration, DeclIndex>           File::enumerations() const
    {
        return impl_->get_and_cache_partition<Enumeration, DeclIndex>();
    }

    Partition<Enumerator, DeclIndex>            File::enumerators() const
    {
        return impl_->get_and_cache_partition<Enumerator, DeclIndex>();
    }

    Partition<AliasDeclaration, DeclIndex>      File::alias_declarations() const
    {
        return impl_->get_and_cache_partition<AliasDeclaration, DeclIndex>();
    }

    Partition<DeclReference, DeclIndex>         File::decl_references() const
    {
        return impl_->get_and_cache_partition<DeclReference, DeclIndex>();
    }

    Partition<FunctionDeclaration, DeclIndex>   File::functions() const
    {
        return impl_->get_and_cache_partition<FunctionDeclaration, DeclIndex>();
    }

    Partition<MethodDeclaration, DeclIndex>     File::methods() const
    {
        return impl_->get_and_cache_partition<MethodDeclaration, DeclIndex>();
    }

    Partition<Constructor, DeclIndex>           File::constructors() const
    {
        return impl_->get_and_cache_partition<Constructor, DeclIndex>();
    }

    Partition<Destructor, DeclIndex>            File::destructors() const
    {
        return impl_->get_and_cache_partition<Destructor, DeclIndex>();
    }

    Partition<VariableDeclaration, DeclIndex>   File::variables() const
    {
        return impl_->get_and_cache_partition<VariableDeclaration, DeclIndex>();
    }

    Partition<ParameterDeclaration, DeclIndex>  File::parameters() const
    {
        return impl_->get_and_cache_partition<ParameterDeclaration, DeclIndex>();
    }

    Partition<FieldDeclaration, DeclIndex>      File::fields() const
    {
        return impl_->get_and_cache_partition<FieldDeclaration, DeclIndex>();
    }

    Partition<FriendDeclaration, DeclIndex>     File::friends() const
    {
        return impl_->get_and_cache_partition<FriendDeclaration, DeclIndex>();
    }

    Partition<Concept, DeclIndex>               File::concepts() const
    {
        return impl_->get_and_cache_partition<Concept, DeclIndex>();
    }

    Partition<IntrinsicDeclaration, DeclIndex>  File::intrinsic_declarations() const
    {
        return impl_->get_and_cache_partition<IntrinsicDeclaration, DeclIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<SpecializationForm, SpecFormIndex> File::specialization_forms() const
    {
        return impl_->get_and_cache_partition<SpecializationForm, SpecFormIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<FundamentalType, TypeIndex>    File::fundamental_types() const 
    {
        return impl_->get_and_cache_partition<FundamentalType, TypeIndex>();
    }
    
    Partition<DesignatedType, TypeIndex>     File::designated_types() const 
    {
        return impl_->get_and_cache_partition<DesignatedType, TypeIndex>();
    }
    
    Partition<TorType, TypeIndex>            File::tor_types() const 
    {
        return impl_->get_and_cache_partition<TorType, TypeIndex>();
    }
    
    Partition<SyntacticType, TypeIndex>      File::syntactic_types() const 
    {
        return impl_->get_and_cache_partition<SyntacticType, TypeIndex>();
    }
    
    Partition<ExpansionType, TypeIndex>      File::expansion_types() const 
    {
        return impl_->get_and_cache_partition<ExpansionType, TypeIndex>();
    }
    
    Partition<PointerType, TypeIndex>        File::pointer_types() const 
    {
        return impl_->get_and_cache_partition<PointerType, TypeIndex>();
    }
    
    Partition<FunctionType, TypeIndex>       File::function_types() const 
    {
        return impl_->get_and_cache_partition<FunctionType, TypeIndex>();
    }
    
    Partition<MethodType, TypeIndex>         File::method_types() const 
    {
        return impl_->get_and_cache_partition<MethodType, TypeIndex>();
    }
    
    Partition<ArrayType, TypeIndex>          File::array_types() const 
    {
        return impl_->get_and_cache_partition<ArrayType, TypeIndex>();
    }
    
    Partition<BaseType, TypeIndex>           File::base_types() const 
    {
        return impl_->get_and_cache_partition<BaseType, TypeIndex>();
    }
    
    Partition<TupleType, TypeIndex>          File::tuple_types() const 
    {
        return impl_->get_and_cache_partition<TupleType, TypeIndex>();
    }
    
    Partition<LvalueReference, TypeIndex>    File::lvalue_references() const 
    {
        return impl_->get_and_cache_partition<LvalueReference, TypeIndex>();
    }
    
    Partition<RvalueReference, TypeIndex>    File::rvalue_references() const 
    {
        return impl_->get_and_cache_partition<RvalueReference, TypeIndex>();
    }
    
    Partition<QualifiedType, TypeIndex>      File::qualified_types() const 
    {
        return impl_->get_and_cache_partition<QualifiedType, TypeIndex>();
    }
    
    Partition<ForallType, TypeIndex>         File::forall_types() const 
    {
        return impl_->get_and_cache_partition<ForallType, TypeIndex>();
    }
    
    Partition<SyntaxType, TypeIndex>         File::syntax_types() const 
    {
        return impl_->get_and_cache_partition<SyntaxType, TypeIndex>();
    }
    
    Partition<PlaceholderType, TypeIndex>    File::placeholder_types() const 
    {
        return impl_->get_and_cache_partition<PlaceholderType, TypeIndex>();
    }
    
    Partition<TypenameType, TypeIndex>       File::typename_types() const 
    {
        return impl_->get_and_cache_partition<TypenameType, TypeIndex>();
    }
    
    Partition<DecltypeType, TypeIndex>       File::decltype_types() const 
    {
        return impl_->get_and_cache_partition<DecltypeType, TypeIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<AttrBasic, AttrIndex> File::basic_attributes() const
    {
        return impl_->get_and_cache_partition<AttrBasic, AttrIndex>();
    }

    Partition<AttrScoped, AttrIndex> File::scoped_attributes() const
    {
        return impl_->get_and_cache_partition<AttrScoped, AttrIndex>();
    }

    Partition<AttrLabeled, AttrIndex> File::labeled_attributes() const
    {
        return impl_->get_and_cache_partition<AttrLabeled, AttrIndex>();
    }

    Partition<AttrCalled, AttrIndex> File::called_attributes() const
    {
        return impl_->get_and_cache_partition<AttrCalled, AttrIndex>();
    }

    Partition<AttrExpanded, AttrIndex> File::expanded_attributes() const
    {
        return impl_->get_and_cache_partition<AttrExpanded, AttrIndex>();
    }

    Partition<AttrFactored, AttrIndex> File::factored_attributes() const
    {
        return impl_->get_and_cache_partition<AttrFactored, AttrIndex>();
    }

    Partition<AttrElaborated, AttrIndex> File::elaborated_attributes() const
    {
        return impl_->get_and_cache_partition<AttrElaborated, AttrIndex>();
    }

    Partition<AttrTuple, AttrIndex> File::tuple_attributes() const
    {
        return impl_->get_and_cache_partition<AttrTuple, AttrIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<LiteralExpression, ExprIndex>  File::literal_expressions() const
    {
        return impl_->get_and_cache_partition<LiteralExpression, ExprIndex>();
    }

    Partition<TypeExpression, ExprIndex>     File::type_expressions() const
    {
        return impl_->get_and_cache_partition<TypeExpression, ExprIndex>();
    }

    Partition<NamedDecl, ExprIndex>          File::decl_expressions() const
    {
        return impl_->get_and_cache_partition<NamedDecl, ExprIndex>();
    }

    Partition<UnqualifiedId, ExprIndex>      File::unqualified_id_expressions() const
    {
        return impl_->get_and_cache_partition<UnqualifiedId, ExprIndex>();
    }

    Partition<TemplateId, ExprIndex>         File::template_ids() const
    {
        return impl_->get_and_cache_partition<TemplateId, ExprIndex>();
    }

    Partition<TemplateReference, ExprIndex>  File::template_references() const
    {
        return impl_->get_and_cache_partition<TemplateReference, ExprIndex>();
    }

    Partition<MonadExpression, ExprIndex>    File::monad_expressions() const
    {
        return impl_->get_and_cache_partition<MonadExpression, ExprIndex>();
    }

    Partition<DyadExpression, ExprIndex>     File::dyad_expressions() const
    {
        return impl_->get_and_cache_partition<DyadExpression, ExprIndex>();
    }

    Partition<StringExpression, ExprIndex>   File::string_expressions() const
    {
        return impl_->get_and_cache_partition<StringExpression, ExprIndex>();
    }

    Partition<CallExpression, ExprIndex>     File::call_expressions() const
    {
        return impl_->get_and_cache_partition<CallExpression, ExprIndex>();
    }

    Partition<SizeofExpression, ExprIndex>   File::sizeof_expressions() const
    {
        return impl_->get_and_cache_partition<SizeofExpression, ExprIndex>();
    }

    Partition<AlignofExpression, ExprIndex>  File::alignof_expressions() const
    {
        return impl_->get_and_cache_partition<AlignofExpression, ExprIndex>();
    }

    Partition<RequiresExpression, ExprIndex> File::requires_expressions() const
    {
        return impl_->get_and_cache_partition<RequiresExpression, ExprIndex>();
    }

    Partition<TupleExpression, ExprIndex>    File::tuple_expressions() const
    {
        return impl_->get_and_cache_partition<TupleExpression, ExprIndex>();
    }

    Partition<PathExpression, ExprIndex>     File::path_expressions() const
    {
        return impl_->get_and_cache_partition<PathExpression, ExprIndex>();
    }

    Partition<ReadExpression, ExprIndex>     File::read_expressions() const
    {
        return impl_->get_and_cache_partition<ReadExpression, ExprIndex>();
    }

    Partition<SyntaxTreeExpression, ExprIndex>  File::syntax_tree_expressions() const
    {
        return impl_->get_and_cache_partition<SyntaxTreeExpression, ExprIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<ExpressionListExpression, ExprIndex> File::expression_lists() const
    {
        return impl_->get_and_cache_partition<ExpressionListExpression, ExprIndex>();
    }

    Partition<QualifiedNameExpression, ExprIndex>  File::qualified_name_expressions() const
    {
        return impl_->get_and_cache_partition<QualifiedNameExpression, ExprIndex>();
    }

    Partition<PackedTemplateArguments, ExprIndex>  File::packed_template_arguments() const
    {
        return impl_->get_and_cache_partition<PackedTemplateArguments, ExprIndex>();
    }

    Partition<ProductValueTypeExpression, ExprIndex>  File::product_value_type_expressions() const
    {
        return impl_->get_and_cache_partition<ProductValueTypeExpression, ExprIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<StringLiteral, StringIndex> File::string_literal_expressions() const
    {
        return impl_->get_and_cache_partition<StringLiteral, StringIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<ChartUnilevel, ChartIndex>    File::unilevel_charts() const
    {
        return impl_->get_and_cache_partition<ChartUnilevel, ChartIndex>();
    }

    Partition<ChartMultilevel, ChartIndex>  File::multilevel_charts() const
    {
        return impl_->get_and_cache_partition<ChartMultilevel, ChartIndex>();

    }

    Partition<IntegerLiteral, LitIndex> File::integer_literals() const 
    {
        return impl_->get_and_cache_partition<IntegerLiteral, LitIndex>();
    }
    Partition<FPLiteral, LitIndex>      File::fp_literals() const 
    {
        return impl_->get_and_cache_partition<FPLiteral, LitIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<SimpleTypeSpecifier, SyntaxIndex>         File::simple_type_specifiers() const
    {
        return impl_->get_and_cache_partition<SimpleTypeSpecifier, SyntaxIndex>();
    }

    Partition<DecltypeSpecifier, SyntaxIndex>           File::decltype_specifiers() const
    {
        return impl_->get_and_cache_partition<DecltypeSpecifier, SyntaxIndex>();
    }

    Partition<TypeSpecifierSeq, SyntaxIndex>            File::type_specifier_seq_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeSpecifierSeq, SyntaxIndex>();
    }

    Partition<DeclSpecifierSeq, SyntaxIndex>            File::decl_specifier_seq_syntax_trees() const
    {
        return impl_->get_and_cache_partition<DeclSpecifierSeq, SyntaxIndex>();
    }

    Partition<TypeIdSyntax, SyntaxIndex>                File::typeid_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeIdSyntax, SyntaxIndex>();
    }

    Partition<DeclaratorSyntax, SyntaxIndex>            File::declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<DeclaratorSyntax, SyntaxIndex>();
    }

    Partition<PointerDeclaratorSyntax, SyntaxIndex>     File::pointer_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<PointerDeclaratorSyntax, SyntaxIndex>();
    }

    Partition<FunctionDeclaratorSyntax, SyntaxIndex>    File::function_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<FunctionDeclaratorSyntax, SyntaxIndex>();
    }

    Partition<ParameterDeclaratorSyntax, SyntaxIndex>   File::parameter_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<ParameterDeclaratorSyntax, SyntaxIndex>();
    }

    Partition<ExpressionSyntax, SyntaxIndex>            File::expression_syntax_trees() const
    {
        return impl_->get_and_cache_partition<ExpressionSyntax, SyntaxIndex>();
    }

    Partition<RequiresClauseSyntax, SyntaxIndex>        File::requires_clause_syntax_trees() const
    {
        return impl_->get_and_cache_partition<RequiresClauseSyntax, SyntaxIndex>();
    }

    Partition<SimpleRequirementSyntax, SyntaxIndex>     File::simple_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<SimpleRequirementSyntax, SyntaxIndex>();
    }

    Partition<TypeRequirementSyntax, SyntaxIndex>       File::type_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeRequirementSyntax, SyntaxIndex>();
    }

    Partition<NestedRequirementSyntax, SyntaxIndex>     File::nested_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<NestedRequirementSyntax, SyntaxIndex>();
    }

    Partition<CompoundRequirementSyntax, SyntaxIndex>   File::compound_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<CompoundRequirementSyntax, SyntaxIndex>();
    }

    Partition<RequirementBodySyntax, SyntaxIndex>       File::requirement_body_syntax_trees() const
    {
        return impl_->get_and_cache_partition<RequirementBodySyntax, SyntaxIndex>();
    }

    Partition<TypeTemplateArgumentSyntax, SyntaxIndex>  File::type_template_argument_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeTemplateArgumentSyntax, SyntaxIndex>();
    }

    Partition<TemplateArgumentListSyntax, SyntaxIndex>  File::template_argument_list_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TemplateArgumentListSyntax, SyntaxIndex>();
    }

    Partition<TemplateIdSyntax, SyntaxIndex>            File::templateid_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TemplateIdSyntax, SyntaxIndex>();
    }

    Partition<TypeTraitIntrinsicSyntax, SyntaxIndex>    File::type_trait_intrinsic_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeTraitIntrinsicSyntax, SyntaxIndex>();
    }

    Partition<TupleSyntax, SyntaxIndex>                 File::tuple_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TupleSyntax, SyntaxIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<OperatorFunctionName, NameIndex> File::operator_names() const
    {
        return impl_->get_and_cache_partition<OperatorFunctionName, NameIndex>();
    }

    Partition<SpecializationName, NameIndex> File::specialization_names() const
    {
        return impl_->get_and_cache_partition<SpecializationName, NameIndex>();
    }

    Partition<LiteralName, NameIndex> File::literal_names() const
    {
        return impl_->get_and_cache_partition<LiteralName, NameIndex>();
    }

    // ------------------------------------------------------------------------

    Partition<TypeIndex, Index> File::type_heap() const
    {
        return impl_->get_and_cache_partition<TypeIndex, Index>("heap.type");
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return impl_->get_and_cache_partition<ExprIndex, Index>("heap.expr");
    }

    Partition<AttrIndex, Index> File::attr_heap() const
    {
        return impl_->get_and_cache_partition<AttrIndex, Index>("heap.attr");
    }

    Partition<SyntaxIndex, Index> File::syntax_heap() const
    {
        return impl_->get_and_cache_partition<SyntaxIndex, Index>("heap.syn");
    }

    Partition<ModuleReference, Index> File::imported_modules() const
    {
        return impl_->get_and_cache_partition<ModuleReference, Index>("module.imported");
    }

    Partition<ModuleReference, Index> File::exported_modules() const
    {
        return impl_->get_and_cache_partition<ModuleReference, Index>("module.exported");
    }

    // ------------------------------------------------------------------------

    Partition<DeclIndex> File::deduction_guides() const
    {
        return impl_->get_and_cache_partition<DeclIndex, uint32_t>("name.guide");
    }

    // ------------------------------------------------------------------------

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

    // ------------------------------------------------------------------------

    File::File(BlobView data)
        : impl_(std::make_unique<Impl>(data))
    {
    }

    File::~File() = default;

    File::File           (File&&) noexcept = default;
    File& File::operator=(File&&) noexcept = default;

    // ------------------------------------------------------------------------

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
