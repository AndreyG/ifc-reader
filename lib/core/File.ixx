module;

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <string_view>

export module ifc;

export import :Attribute;
export import :Chart;
export import :ChartIndex;
export import :Declaration;
export import :DeclIndex;
export import :Expression;
export import :ExprIndex;
export import :Name;
export import :NameIndex;
export import :SyntaxTree;
export import :SyntaxIndex;
export import :Type;
export import :TypeIndex;

export import ifc.common_types;
import ifc.AbstractReference;
import ifc.FileHeader;
import ifc.Literal;
import ifc.Module;
import ifc.Partition;
import ifc.Scope;

export namespace ifc
{
    class File
    {
    public:
        FileHeader const & header() const;

        std::span<PartitionSummary const> table_of_contents() const;

        const char * get_string(TextOffset) const;

        Sequence global_scope() const;

        ScopePartition scope_descriptors() const;

        std::byte const* get_data_pointer(PartitionSummary const&) const;

        // Declarations
        Partition<Declaration, Index>               declarations() const;

        Partition<ScopeDeclaration, DeclIndex>      scope_declarations() const;
        Partition<TemplateDeclaration, DeclIndex>   template_declarations() const;
        Partition<PartialSpecialization, DeclIndex> partial_specializations() const;
        Partition<Specialization, DeclIndex>        specializations() const;
        Partition<UsingDeclaration, DeclIndex>      using_declarations() const;
        Partition<Enumeration, DeclIndex>           enumerations() const;
        Partition<Enumerator, DeclIndex>            enumerators() const;
        Partition<AliasDeclaration, DeclIndex>      alias_declarations() const;
        Partition<DeclReference, DeclIndex>         decl_references() const;
        Partition<FunctionDeclaration, DeclIndex>   functions() const;
        Partition<MethodDeclaration, DeclIndex>     methods() const;
        Partition<Constructor, DeclIndex>           constructors() const;
        Partition<Destructor, DeclIndex>            destructors() const;
        Partition<VariableDeclaration, DeclIndex>   variables() const;
        Partition<ParameterDeclaration, DeclIndex>  parameters() const;
        Partition<FieldDeclaration, DeclIndex>      fields() const;
        Partition<FriendDeclaration, DeclIndex>     friends() const;
        Partition<Concept, DeclIndex>               concepts() const;
        Partition<IntrinsicDeclaration, DeclIndex>  intrinsic_declarations() const;

        Partition<SpecializationForm, SpecFormIndex> specialization_forms() const;

        // Types
        Partition<FundamentalType, TypeIndex>    fundamental_types() const;
        Partition<DesignatedType, TypeIndex>     designated_types() const;
        Partition<TorType, TypeIndex>            tor_types() const;
        Partition<SyntacticType, TypeIndex>      syntactic_types() const;
        Partition<ExpansionType, TypeIndex>      expansion_types() const;
        Partition<PointerType, TypeIndex>        pointer_types() const;
        Partition<FunctionType, TypeIndex>       function_types() const;
        Partition<MethodType, TypeIndex>         method_types() const;
        Partition<ArrayType, TypeIndex>          array_types() const;
        Partition<BaseType, TypeIndex>           base_types() const;
        Partition<TupleType, TypeIndex>          tuple_types() const;
        Partition<LvalueReference, TypeIndex>    lvalue_references() const;
        Partition<RvalueReference, TypeIndex>    rvalue_references() const;
        Partition<QualifiedType, TypeIndex>      qualified_types() const;
        Partition<ForallType, TypeIndex>         forall_types() const;
        Partition<SyntaxType, TypeIndex>         syntax_types() const;
        Partition<PlaceholderType, TypeIndex>    placeholder_types() const;
        Partition<TypenameType, TypeIndex>       typename_types() const;
        Partition<DecltypeType, TypeIndex>       decltype_types() const;

        // Attributes
        Partition<AttrBasic, AttrIndex>         basic_attributes() const;
        Partition<AttrScoped, AttrIndex>        scoped_attributes() const;
        Partition<AttrLabeled, AttrIndex>       labeled_attributes() const;
        Partition<AttrCalled, AttrIndex>        called_attributes() const;
        Partition<AttrExpanded, AttrIndex>      expanded_attributes() const;
        Partition<AttrFactored, AttrIndex>      factored_attributes() const;
        Partition<AttrElaborated, AttrIndex>    elaborated_attributes() const;
        Partition<AttrTuple, AttrIndex>         tuple_attributes() const;

        // Expressions
        Partition<LiteralExpression, ExprIndex>             literal_expressions() const;
        Partition<TypeExpression, ExprIndex>                type_expressions() const;
        Partition<NamedDecl, ExprIndex>                     decl_expressions() const;
        Partition<UnqualifiedId, ExprIndex>                 unqualified_id_expressions() const;
        Partition<TemplateId, ExprIndex>                    template_ids() const;
        Partition<TemplateReference, ExprIndex>             template_references() const;
        Partition<MonadExpression, ExprIndex>               monad_expressions() const;
        Partition<DyadExpression, ExprIndex>                dyad_expressions() const;
        Partition<StringExpression, ExprIndex>              string_expressions() const;
        Partition<CallExpression, ExprIndex>                call_expressions() const;
        Partition<SizeofExpression, ExprIndex>              sizeof_expressions() const;
        Partition<AlignofExpression, ExprIndex>             alignof_expressions() const;
        Partition<RequiresExpression, ExprIndex>            requires_expressions() const;
        Partition<TupleExpression, ExprIndex>               tuple_expressions() const;
        Partition<PathExpression, ExprIndex>                path_expressions() const;
        Partition<ReadExpression, ExprIndex>                read_expressions() const;
        Partition<SyntaxTreeExpression, ExprIndex>          syntax_tree_expressions() const;

        Partition<ExpressionListExpression, ExprIndex>      expression_lists() const;
        Partition<QualifiedNameExpression, ExprIndex>       qualified_name_expressions() const;
        Partition<PackedTemplateArguments, ExprIndex>       packed_template_arguments() const;
        Partition<ProductValueTypeExpression, ExprIndex>    product_value_type_expressions() const;

        Partition<StringLiteral, StringIndex> string_literal_expressions() const;

        // Heaps
        Partition<TypeIndex, Index>     type_heap() const;
        Partition<ExprIndex, Index>     expr_heap() const;
        Partition<AttrIndex, Index>     attr_heap() const;
        Partition<SyntaxIndex, Index>   syntax_heap() const;

        // Names
        Partition<OperatorFunctionName, NameIndex>  operator_names() const;
        Partition<SpecializationName, NameIndex>    specialization_names() const;
        Partition<LiteralName, NameIndex>           literal_names() const;

        // Charts
        Partition<ChartUnilevel, ChartIndex>    unilevel_charts() const;
        Partition<ChartMultilevel, ChartIndex>  multilevel_charts() const;

        // Literals
        Partition<IntegerLiteral, LitIndex> integer_literals() const;
        Partition<FPLiteral, LitIndex>      fp_literals() const;

        // Syntax Trees
        Partition<SimpleTypeSpecifier, SyntaxIndex>        simple_type_specifiers() const;
        Partition<DecltypeSpecifier, SyntaxIndex>          decltype_specifiers() const;
        Partition<TypeSpecifierSeq, SyntaxIndex>           type_specifier_seq_syntax_trees() const;
        Partition<DeclSpecifierSeq, SyntaxIndex>           decl_specifier_seq_syntax_trees() const;
        Partition<TypeIdSyntax, SyntaxIndex>               typeid_syntax_trees() const;
        Partition<DeclaratorSyntax, SyntaxIndex>           declarator_syntax_trees() const;
        Partition<PointerDeclaratorSyntax, SyntaxIndex>    pointer_declarator_syntax_trees() const;
        Partition<FunctionDeclaratorSyntax, SyntaxIndex>   function_declarator_syntax_trees() const;
        Partition<ParameterDeclaratorSyntax, SyntaxIndex>  parameter_declarator_syntax_trees() const;
        Partition<ExpressionSyntax, SyntaxIndex>           expression_syntax_trees() const;
        Partition<RequiresClauseSyntax, SyntaxIndex>       requires_clause_syntax_trees() const;
        Partition<SimpleRequirementSyntax, SyntaxIndex>    simple_requirement_syntax_trees() const;
        Partition<TypeRequirementSyntax, SyntaxIndex>      type_requirement_syntax_trees() const;
        Partition<NestedRequirementSyntax, SyntaxIndex>    nested_requirement_syntax_trees() const;
        Partition<CompoundRequirementSyntax, SyntaxIndex>  compound_requirement_syntax_trees() const;
        Partition<RequirementBodySyntax, SyntaxIndex>      requirement_body_syntax_trees() const;
        Partition<TypeTemplateArgumentSyntax, SyntaxIndex> type_template_argument_syntax_trees() const;
        Partition<TemplateArgumentListSyntax, SyntaxIndex> template_argument_list_syntax_trees() const;
        Partition<TemplateIdSyntax, SyntaxIndex>           templateid_syntax_trees() const;
        Partition<TypeTraitIntrinsicSyntax, SyntaxIndex>   type_trait_intrinsic_syntax_trees() const;
        Partition<TupleSyntax, SyntaxIndex>                tuple_syntax_trees() const;

        // Module References
        Partition<ModuleReference, Index> imported_modules() const;
        Partition<ModuleReference, Index> exported_modules() const;

        // Deduction guides
        Partition<DeclIndex> deduction_guides() const;

    public:
        // Traits
        TextOffset                  trait_deprecation_texts     (DeclIndex) const;
        std::span<AttrIndex const>  trait_declaration_attributes(DeclIndex) const;
        Sequence                    trait_friendship_of_class   (DeclIndex) const; // A sequence that indexes into the "scope.member" partition

    public:
        using BlobView = std::span<std::byte const>;

        explicit File(BlobView);
        ~File();

        File           (File &&) noexcept;
        File& operator=(File &&) noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };

    ScopeDeclaration const &        get_scope       (File const&, DeclIndex);
    Partition<Declaration, Index>   get_declarations(File const&, Sequence);
    Partition<ExprIndex, Index>     get_tuple_expression_elements(File const&, TupleExpression const&);

    Partition<ExprIndex, Index>     get_qualified_name_parts(File const& ifc, QualifiedNameExpression const&);

    TypeBasis get_kind(ScopeDeclaration const&, File const&);
}

export template<int N, typename Sort>
struct std::hash<ifc::AbstractReference<N, Sort>>
{
	std::size_t operator()(ifc::AbstractReference<N, Sort> s) const noexcept
	{
		using std::uint32_t;
		return std::hash<uint32_t>{}(reinterpret_cast<uint32_t&>(s));
	}
};

module :private;

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

        enum class FilePartitionCache : uint32_t
        {
            Declarations,
            ScopeDeclarations,
            TemplateDeclarations,
            PartialSpecializations,
            Specializations,
            UsingDeclarations,
            Enumerations,
            Enumerators,
            AliasDeclarations,
            DeclReferences,
            Functions,
            Methods,
            Constructors,
            Destructors,
            Variables,
            Parameters,
            Fields,
            Friends,
            Concepts,
            IntrinsicDeclarations,
            SpecializationForms,
            FundamentalTypes,
            DesignatedTypes,
            TorTypes,
            SyntacticTypes,
            ExpansionTypes,
            PointerTypes,
            FunctionTypes,
            MethodTypes,
            ArrayTypes,
            BaseTypes,
            TupleTypes,
            LvalueReferences,
            RvalueReferences,
            QualifiedTypes,
            ForallTypes,
            SyntaxTypes,
            PlaceholderTypes,
            TypenameTypes,
            DecltypeTypes,
            BasicAttributes,
            ScopedAttributes,
            LabeledAttributes,
            CalledAttributes,
            ExpandedAttributes,
            FactoredAttributes,
            ElaboratedAttributes,
            TupleAttributes,
            LiteralExpressions,
            TypeExpressions,
            DeclExpressions,
            UnqualifiedIdExpressions,
            TemplateIds,
            TemplateReferences,
            MonadExpressions,
            DyadExpressions,
            StringExpressions,
            CallExpressions,
            SizeofExpressions,
            AlignofExpressions,
            RequiresExpressions,
            TupleExpressions,
            PathExpressions,
            ReadExpressions,
            SyntaxTreeExpressions,
            ExpressionLists,
            QualifiedNameExpressions,
            PackedTemplateArguments,
            ProductValueTypeExpressions,
            StringLiteralExpressions,
            TypeHeap,
            ExprHeap,
            AttrHeap,
            SyntaxHeap,
            OperatorNames,
            SpecializationNames,
            LiteralNames,
            UnilevelCharts,
            MultilevelCharts,
            IntegerLiterals,
            FpLiterals,
            SimpleTypeSpecifiers,
            DecltypeSpecifiers,
            TypeSpecifierSeqSyntaxTrees,
            DeclSpecifierSeqSyntaxTrees,
            TypeidSyntaxTrees,
            DeclaratorSyntaxTrees,
            PointerDeclaratorSyntaxTrees,
            FunctionDeclaratorSyntaxTrees,
            ParameterDeclaratorSyntaxTrees,
            ExpressionSyntaxTrees,
            RequiresClauseSyntaxTrees,
            SimpleRequirementSyntaxTrees,
            TypeRequirementSyntaxTrees,
            NestedRequirementSyntaxTrees,
            CompoundRequirementSyntaxTrees,
            RequirementBodySyntaxTrees,
            TypeTemplateArgumentSyntaxTrees,
            TemplateArgumentListSyntaxTrees,
            TemplateidSyntaxTrees,
            TypeTraitIntrinsicSyntaxTrees,
            TupleSyntaxTrees,
            ImportedModules,
            ExportedModules,
            DeductionGuides,

            Num,
        };

        template<typename T>
        struct AssociatedTrait
        {
            DeclIndex decl;
            T trait;
        };
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
        Partition<T, Index> get_and_cache_partition(FilePartitionCache cache_type) const
        {
            return get_and_cache_partition<T, Index>(T::PartitionName, cache_type);
        }

        template<typename T, typename Index>
        Partition<T, Index> get_and_cache_partition(std::string_view name, FilePartitionCache cache_type) const
        {
            auto const cache_index = (uint32_t)cache_type;

            if (auto& cached_partition = cached_partitions_[cache_index])
            {
                auto partition = *cached_partition;
                return { static_cast<T const*>(partition.data), partition.size };
            }
            else
            {
                auto result = get_partition<T, Index>(table_of_contents_.at(name));
                cached_partition.emplace(result.data(), result.size());
                return result;
            }
        }

        using DeclIndexHasher = decltype([](DeclIndex decl) noexcept { return std::hash<uint32_t>{}(reinterpret_cast<uint32_t&>(decl)); });

        std::unordered_map<DeclIndex, std::vector<AttrIndex>, DeclIndexHasher> const & trait_declaration_attributes()
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

        std::unordered_map<DeclIndex, TextOffset, DeclIndexHasher> const & trait_deprecation_texts()
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

        std::unordered_map<DeclIndex, Sequence, DeclIndexHasher> const& trait_friendship_of_class()
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

        std::optional<std::unordered_map<DeclIndex, TextOffset, DeclIndexHasher>> trait_deprecation_texts_;
        std::optional<std::unordered_map<DeclIndex, std::vector<AttrIndex>, DeclIndexHasher>> trait_declaration_attributes_;
        std::optional<std::unordered_map<DeclIndex, Sequence, DeclIndexHasher>> trait_friendship_of_class_;

        struct UntypedPartition
        {
            const void* data;
            size_t      size;
        };
        using CachedPartition = std::optional<UntypedPartition>;

        mutable std::array<CachedPartition, (size_t)FilePartitionCache::Num> cached_partitions_{};
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

    // ------------------------------------------------------------------------

    Partition<Declaration, Index> File::declarations() const
    {
        return impl_->get_and_cache_partition<Declaration, Index>(FilePartitionCache::Declarations);
    }

    Partition<ScopeDeclaration, DeclIndex> File::scope_declarations() const
    {
        return impl_->get_and_cache_partition<ScopeDeclaration, DeclIndex>(FilePartitionCache::ScopeDeclarations);
    }

    Partition<TemplateDeclaration, DeclIndex> File::template_declarations() const
    {
        return impl_->get_and_cache_partition<TemplateDeclaration, DeclIndex>(FilePartitionCache::TemplateDeclarations);
    }

    Partition<PartialSpecialization, DeclIndex> File::partial_specializations() const
    {
        return impl_->get_and_cache_partition<PartialSpecialization, DeclIndex>(FilePartitionCache::PartialSpecializations);
    }

    Partition<Specialization, DeclIndex> File::specializations() const
    {
        return impl_->get_and_cache_partition<Specialization, DeclIndex>(FilePartitionCache::Specializations);
    }

    Partition<UsingDeclaration, DeclIndex> File::using_declarations() const
    {
        return impl_->get_and_cache_partition<UsingDeclaration, DeclIndex>(FilePartitionCache::UsingDeclarations);
    }

    Partition<Enumeration, DeclIndex> File::enumerations() const
    {
        return impl_->get_and_cache_partition<Enumeration, DeclIndex>(FilePartitionCache::Enumerations);
    }

    Partition<Enumerator, DeclIndex> File::enumerators() const
    {
        return impl_->get_and_cache_partition<Enumerator, DeclIndex>(FilePartitionCache::Enumerators);
    }

    Partition<AliasDeclaration, DeclIndex> File::alias_declarations() const
    {
        return impl_->get_and_cache_partition<AliasDeclaration, DeclIndex>(FilePartitionCache::AliasDeclarations);
    }

    Partition<DeclReference, DeclIndex> File::decl_references() const
    {
        return impl_->get_and_cache_partition<DeclReference, DeclIndex>(FilePartitionCache::DeclReferences);
    }

    Partition<FunctionDeclaration, DeclIndex> File::functions() const
    {
        return impl_->get_and_cache_partition<FunctionDeclaration, DeclIndex>(FilePartitionCache::Functions);
    }

    Partition<MethodDeclaration, DeclIndex> File::methods() const
    {
        return impl_->get_and_cache_partition<MethodDeclaration, DeclIndex>(FilePartitionCache::Methods);
    }

    Partition<Constructor, DeclIndex> File::constructors() const
    {
        return impl_->get_and_cache_partition<Constructor, DeclIndex>(FilePartitionCache::Constructors);
    }

    Partition<Destructor, DeclIndex> File::destructors() const
    {
        return impl_->get_and_cache_partition<Destructor, DeclIndex>(FilePartitionCache::Destructors);
    }

    Partition<VariableDeclaration, DeclIndex> File::variables() const
    {
        return impl_->get_and_cache_partition<VariableDeclaration, DeclIndex>(FilePartitionCache::Variables);
    }

    Partition<ParameterDeclaration, DeclIndex> File::parameters() const
    {
        return impl_->get_and_cache_partition<ParameterDeclaration, DeclIndex>(FilePartitionCache::Parameters);
    }

    Partition<FieldDeclaration, DeclIndex> File::fields() const
    {
        return impl_->get_and_cache_partition<FieldDeclaration, DeclIndex>(FilePartitionCache::Fields);
    }

    Partition<FriendDeclaration, DeclIndex> File::friends() const
    {
        return impl_->get_and_cache_partition<FriendDeclaration, DeclIndex>(FilePartitionCache::Friends);
    }

    Partition<Concept, DeclIndex> File::concepts() const
    {
        return impl_->get_and_cache_partition<Concept, DeclIndex>(FilePartitionCache::Concepts);
    }

    Partition<IntrinsicDeclaration, DeclIndex> File::intrinsic_declarations() const
    {
        return impl_->get_and_cache_partition<IntrinsicDeclaration, DeclIndex>(FilePartitionCache::IntrinsicDeclarations);
    }

    // ------------------------------------------------------------------------

    Partition<SpecializationForm, SpecFormIndex> File::specialization_forms() const
    {
        return impl_->get_and_cache_partition<SpecializationForm, SpecFormIndex>(FilePartitionCache::SpecializationForms);
    }

    // ------------------------------------------------------------------------

    Partition<FundamentalType, TypeIndex> File::fundamental_types() const
    {
        return impl_->get_and_cache_partition<FundamentalType, TypeIndex>(FilePartitionCache::FundamentalTypes);
    }

    Partition<DesignatedType, TypeIndex> File::designated_types() const
    {
        return impl_->get_and_cache_partition<DesignatedType, TypeIndex>(FilePartitionCache::DesignatedTypes);
    }

    Partition<TorType, TypeIndex> File::tor_types() const
    {
        return impl_->get_and_cache_partition<TorType, TypeIndex>(FilePartitionCache::TorTypes);
    }

    Partition<SyntacticType, TypeIndex> File::syntactic_types() const
    {
        return impl_->get_and_cache_partition<SyntacticType, TypeIndex>(FilePartitionCache::SyntacticTypes);
    }

    Partition<ExpansionType, TypeIndex> File::expansion_types() const
    {
        return impl_->get_and_cache_partition<ExpansionType, TypeIndex>(FilePartitionCache::ExpansionTypes);
    }

    Partition<PointerType, TypeIndex> File::pointer_types() const
    {
        return impl_->get_and_cache_partition<PointerType, TypeIndex>(FilePartitionCache::PointerTypes);
    }

    Partition<FunctionType, TypeIndex> File::function_types() const
    {
        return impl_->get_and_cache_partition<FunctionType, TypeIndex>(FilePartitionCache::FunctionTypes);
    }

    Partition<MethodType, TypeIndex> File::method_types() const
    {
        return impl_->get_and_cache_partition<MethodType, TypeIndex>(FilePartitionCache::MethodTypes);
    }

    Partition<ArrayType, TypeIndex> File::array_types() const
    {
        return impl_->get_and_cache_partition<ArrayType, TypeIndex>(FilePartitionCache::ArrayTypes);
    }

    Partition<BaseType, TypeIndex> File::base_types() const
    {
        return impl_->get_and_cache_partition<BaseType, TypeIndex>(FilePartitionCache::BaseTypes);
    }

    Partition<TupleType, TypeIndex> File::tuple_types() const
    {
        return impl_->get_and_cache_partition<TupleType, TypeIndex>(FilePartitionCache::TupleTypes);
    }

    Partition<LvalueReference, TypeIndex> File::lvalue_references() const
    {
        return impl_->get_and_cache_partition<LvalueReference, TypeIndex>(FilePartitionCache::LvalueReferences);
    }

    Partition<RvalueReference, TypeIndex> File::rvalue_references() const
    {
        return impl_->get_and_cache_partition<RvalueReference, TypeIndex>(FilePartitionCache::RvalueReferences);
    }

    Partition<QualifiedType, TypeIndex> File::qualified_types() const
    {
        return impl_->get_and_cache_partition<QualifiedType, TypeIndex>(FilePartitionCache::QualifiedTypes);
    }

    Partition<ForallType, TypeIndex> File::forall_types() const
    {
        return impl_->get_and_cache_partition<ForallType, TypeIndex>(FilePartitionCache::ForallTypes);
    }

    Partition<SyntaxType, TypeIndex> File::syntax_types() const
    {
        return impl_->get_and_cache_partition<SyntaxType, TypeIndex>(FilePartitionCache::SyntaxTypes);
    }

    Partition<PlaceholderType, TypeIndex> File::placeholder_types() const
    {
        return impl_->get_and_cache_partition<PlaceholderType, TypeIndex>(FilePartitionCache::PlaceholderTypes);
    }

    Partition<TypenameType, TypeIndex> File::typename_types() const
    {
        return impl_->get_and_cache_partition<TypenameType, TypeIndex>(FilePartitionCache::TypenameTypes);
    }

    Partition<DecltypeType, TypeIndex> File::decltype_types() const
    {
        return impl_->get_and_cache_partition<DecltypeType, TypeIndex>(FilePartitionCache::DecltypeTypes);
    }

    // ------------------------------------------------------------------------

    Partition<AttrBasic, AttrIndex> File::basic_attributes() const
    {
        return impl_->get_and_cache_partition<AttrBasic, AttrIndex>(FilePartitionCache::BasicAttributes);
    }

    Partition<AttrScoped, AttrIndex> File::scoped_attributes() const
    {
        return impl_->get_and_cache_partition<AttrScoped, AttrIndex>(FilePartitionCache::ScopedAttributes);
    }

    Partition<AttrLabeled, AttrIndex> File::labeled_attributes() const
    {
        return impl_->get_and_cache_partition<AttrLabeled, AttrIndex>(FilePartitionCache::LabeledAttributes);
    }

    Partition<AttrCalled, AttrIndex> File::called_attributes() const
    {
        return impl_->get_and_cache_partition<AttrCalled, AttrIndex>(FilePartitionCache::CalledAttributes);
    }

    Partition<AttrExpanded, AttrIndex> File::expanded_attributes() const
    {
        return impl_->get_and_cache_partition<AttrExpanded, AttrIndex>(FilePartitionCache::ExpandedAttributes);
    }

    Partition<AttrFactored, AttrIndex> File::factored_attributes() const
    {
        return impl_->get_and_cache_partition<AttrFactored, AttrIndex>(FilePartitionCache::FactoredAttributes);
    }

    Partition<AttrElaborated, AttrIndex> File::elaborated_attributes() const
    {
        return impl_->get_and_cache_partition<AttrElaborated, AttrIndex>(FilePartitionCache::ElaboratedAttributes);
    }

    Partition<AttrTuple, AttrIndex> File::tuple_attributes() const
    {
        return impl_->get_and_cache_partition<AttrTuple, AttrIndex>(FilePartitionCache::TupleAttributes);
    }

    // ------------------------------------------------------------------------

    Partition<LiteralExpression, ExprIndex> File::literal_expressions() const
    {
        return impl_->get_and_cache_partition<LiteralExpression, ExprIndex>(FilePartitionCache::LiteralExpressions);
    }

    Partition<TypeExpression, ExprIndex> File::type_expressions() const
    {
        return impl_->get_and_cache_partition<TypeExpression, ExprIndex>(FilePartitionCache::TypeExpressions);
    }

    Partition<NamedDecl, ExprIndex> File::decl_expressions() const
    {
        return impl_->get_and_cache_partition<NamedDecl, ExprIndex>(FilePartitionCache::DeclExpressions);
    }

    Partition<UnqualifiedId, ExprIndex> File::unqualified_id_expressions() const
    {
        return impl_->get_and_cache_partition<UnqualifiedId, ExprIndex>(FilePartitionCache::UnqualifiedIdExpressions);
    }

    Partition<TemplateId, ExprIndex> File::template_ids() const
    {
        return impl_->get_and_cache_partition<TemplateId, ExprIndex>(FilePartitionCache::TemplateIds);
    }

    Partition<TemplateReference, ExprIndex> File::template_references() const
    {
        return impl_->get_and_cache_partition<TemplateReference, ExprIndex>(FilePartitionCache::TemplateReferences);
    }

    Partition<MonadExpression, ExprIndex> File::monad_expressions() const
    {
        return impl_->get_and_cache_partition<MonadExpression, ExprIndex>(FilePartitionCache::MonadExpressions);
    }

    Partition<DyadExpression, ExprIndex> File::dyad_expressions() const
    {
        return impl_->get_and_cache_partition<DyadExpression, ExprIndex>(FilePartitionCache::DyadExpressions);
    }

    Partition<StringExpression, ExprIndex> File::string_expressions() const
    {
        return impl_->get_and_cache_partition<StringExpression, ExprIndex>(FilePartitionCache::StringExpressions);
    }

    Partition<CallExpression, ExprIndex> File::call_expressions() const
    {
        return impl_->get_and_cache_partition<CallExpression, ExprIndex>(FilePartitionCache::CallExpressions);
    }

    Partition<SizeofExpression, ExprIndex> File::sizeof_expressions() const
    {
        return impl_->get_and_cache_partition<SizeofExpression, ExprIndex>(FilePartitionCache::SizeofExpressions);
    }

    Partition<AlignofExpression, ExprIndex> File::alignof_expressions() const
    {
        return impl_->get_and_cache_partition<AlignofExpression, ExprIndex>(FilePartitionCache::AlignofExpressions);
    }

    Partition<RequiresExpression, ExprIndex> File::requires_expressions() const
    {
        return impl_->get_and_cache_partition<RequiresExpression, ExprIndex>(FilePartitionCache::RequiresExpressions);
    }

    Partition<TupleExpression, ExprIndex> File::tuple_expressions() const
    {
        return impl_->get_and_cache_partition<TupleExpression, ExprIndex>(FilePartitionCache::TupleExpressions);
    }

    Partition<PathExpression, ExprIndex> File::path_expressions() const
    {
        return impl_->get_and_cache_partition<PathExpression, ExprIndex>(FilePartitionCache::PathExpressions);
    }

    Partition<ReadExpression, ExprIndex> File::read_expressions() const
    {
        return impl_->get_and_cache_partition<ReadExpression, ExprIndex>(FilePartitionCache::ReadExpressions);
    }

    Partition<SyntaxTreeExpression, ExprIndex> File::syntax_tree_expressions() const
    {
        return impl_->get_and_cache_partition<SyntaxTreeExpression, ExprIndex>(FilePartitionCache::SyntaxTreeExpressions);
    }

    // ------------------------------------------------------------------------

    Partition<ExpressionListExpression, ExprIndex> File::expression_lists() const
    {
        return impl_->get_and_cache_partition<ExpressionListExpression, ExprIndex>(FilePartitionCache::ExpressionLists);
    }

    Partition<QualifiedNameExpression, ExprIndex> File::qualified_name_expressions() const
    {
        return impl_->get_and_cache_partition<QualifiedNameExpression, ExprIndex>(FilePartitionCache::QualifiedNameExpressions);
    }

    Partition<PackedTemplateArguments, ExprIndex> File::packed_template_arguments() const
    {
        return impl_->get_and_cache_partition<PackedTemplateArguments, ExprIndex>(FilePartitionCache::PackedTemplateArguments);
    }

    Partition<ProductValueTypeExpression, ExprIndex> File::product_value_type_expressions() const
    {
        return impl_->get_and_cache_partition<ProductValueTypeExpression, ExprIndex>(FilePartitionCache::ProductValueTypeExpressions);
    }

    // ------------------------------------------------------------------------

    Partition<StringLiteral, StringIndex> File::string_literal_expressions() const
    {
        return impl_->get_and_cache_partition<StringLiteral, StringIndex>(FilePartitionCache::StringLiteralExpressions);
    }

    // ------------------------------------------------------------------------

    Partition<ChartUnilevel, ChartIndex> File::unilevel_charts() const
    {
        return impl_->get_and_cache_partition<ChartUnilevel, ChartIndex>(FilePartitionCache::UnilevelCharts);
    }

    Partition<ChartMultilevel, ChartIndex> File::multilevel_charts() const
    {
        return impl_->get_and_cache_partition<ChartMultilevel, ChartIndex>(FilePartitionCache::MultilevelCharts);
    }

    Partition<IntegerLiteral, LitIndex> File::integer_literals() const
    {
        return impl_->get_and_cache_partition<IntegerLiteral, LitIndex>(FilePartitionCache::IntegerLiterals);
    }

    Partition<FPLiteral, LitIndex> File::fp_literals() const
    {
        return impl_->get_and_cache_partition<FPLiteral, LitIndex>(FilePartitionCache::FpLiterals);
    }

    // ------------------------------------------------------------------------

    Partition<SimpleTypeSpecifier, SyntaxIndex> File::simple_type_specifiers() const
    {
        return impl_->get_and_cache_partition<SimpleTypeSpecifier, SyntaxIndex>(FilePartitionCache::SimpleTypeSpecifiers);
    }

    Partition<DecltypeSpecifier, SyntaxIndex> File::decltype_specifiers() const
    {
        return impl_->get_and_cache_partition<DecltypeSpecifier, SyntaxIndex>(FilePartitionCache::DecltypeSpecifiers);
    }

    Partition<TypeSpecifierSeq, SyntaxIndex> File::type_specifier_seq_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeSpecifierSeq, SyntaxIndex>(FilePartitionCache::TypeSpecifierSeqSyntaxTrees);
    }

    Partition<DeclSpecifierSeq, SyntaxIndex> File::decl_specifier_seq_syntax_trees() const
    {
        return impl_->get_and_cache_partition<DeclSpecifierSeq, SyntaxIndex>(FilePartitionCache::DeclSpecifierSeqSyntaxTrees);
    }

    Partition<TypeIdSyntax, SyntaxIndex> File::typeid_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeIdSyntax, SyntaxIndex>(FilePartitionCache::TypeidSyntaxTrees);
    }

    Partition<DeclaratorSyntax, SyntaxIndex> File::declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<DeclaratorSyntax, SyntaxIndex>(FilePartitionCache::DeclaratorSyntaxTrees);
    }

    Partition<PointerDeclaratorSyntax, SyntaxIndex> File::pointer_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<PointerDeclaratorSyntax, SyntaxIndex>(FilePartitionCache::PointerDeclaratorSyntaxTrees);
    }

    Partition<FunctionDeclaratorSyntax, SyntaxIndex> File::function_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<FunctionDeclaratorSyntax, SyntaxIndex>(FilePartitionCache::FunctionDeclaratorSyntaxTrees);
    }

    Partition<ParameterDeclaratorSyntax, SyntaxIndex> File::parameter_declarator_syntax_trees() const
    {
        return impl_->get_and_cache_partition<ParameterDeclaratorSyntax, SyntaxIndex>(FilePartitionCache::ParameterDeclaratorSyntaxTrees);
    }

    Partition<ExpressionSyntax, SyntaxIndex> File::expression_syntax_trees() const
    {
        return impl_->get_and_cache_partition<ExpressionSyntax, SyntaxIndex>(FilePartitionCache::ExpressionSyntaxTrees);
    }

    Partition<RequiresClauseSyntax, SyntaxIndex> File::requires_clause_syntax_trees() const
    {
        return impl_->get_and_cache_partition<RequiresClauseSyntax, SyntaxIndex>(FilePartitionCache::RequiresClauseSyntaxTrees);
    }

    Partition<SimpleRequirementSyntax, SyntaxIndex> File::simple_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<SimpleRequirementSyntax, SyntaxIndex>(FilePartitionCache::SimpleRequirementSyntaxTrees);
    }

    Partition<TypeRequirementSyntax, SyntaxIndex> File::type_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeRequirementSyntax, SyntaxIndex>(FilePartitionCache::TypeRequirementSyntaxTrees);
    }

    Partition<NestedRequirementSyntax, SyntaxIndex> File::nested_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<NestedRequirementSyntax, SyntaxIndex>(FilePartitionCache::NestedRequirementSyntaxTrees);
    }

    Partition<CompoundRequirementSyntax, SyntaxIndex> File::compound_requirement_syntax_trees() const
    {
        return impl_->get_and_cache_partition<CompoundRequirementSyntax, SyntaxIndex>(FilePartitionCache::CompoundRequirementSyntaxTrees);
    }

    Partition<RequirementBodySyntax, SyntaxIndex> File::requirement_body_syntax_trees() const
    {
        return impl_->get_and_cache_partition<RequirementBodySyntax, SyntaxIndex>(FilePartitionCache::RequirementBodySyntaxTrees);
    }

    Partition<TypeTemplateArgumentSyntax, SyntaxIndex> File::type_template_argument_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeTemplateArgumentSyntax, SyntaxIndex>(FilePartitionCache::TypeTemplateArgumentSyntaxTrees);
    }

    Partition<TemplateArgumentListSyntax, SyntaxIndex> File::template_argument_list_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TemplateArgumentListSyntax, SyntaxIndex>(FilePartitionCache::TemplateArgumentListSyntaxTrees);
    }

    Partition<TemplateIdSyntax, SyntaxIndex> File::templateid_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TemplateIdSyntax, SyntaxIndex>(FilePartitionCache::TemplateidSyntaxTrees);
    }

    Partition<TypeTraitIntrinsicSyntax, SyntaxIndex> File::type_trait_intrinsic_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TypeTraitIntrinsicSyntax, SyntaxIndex>(FilePartitionCache::TypeTraitIntrinsicSyntaxTrees);
    }

    Partition<TupleSyntax, SyntaxIndex> File::tuple_syntax_trees() const
    {
        return impl_->get_and_cache_partition<TupleSyntax, SyntaxIndex>(FilePartitionCache::TupleSyntaxTrees);
    }

    // ------------------------------------------------------------------------

    Partition<OperatorFunctionName, NameIndex> File::operator_names() const
    {
        return impl_->get_and_cache_partition<OperatorFunctionName, NameIndex>(FilePartitionCache::OperatorNames);
    }

    Partition<SpecializationName, NameIndex> File::specialization_names() const
    {
        return impl_->get_and_cache_partition<SpecializationName, NameIndex>(FilePartitionCache::SpecializationNames);
    }

    Partition<LiteralName, NameIndex> File::literal_names() const
    {
        return impl_->get_and_cache_partition<LiteralName, NameIndex>(FilePartitionCache::LiteralNames);
    }

    // ------------------------------------------------------------------------

    Partition<TypeIndex, Index> File::type_heap() const
    {
        return impl_->get_and_cache_partition<TypeIndex, Index>("heap.type", FilePartitionCache::TypeHeap);
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return impl_->get_and_cache_partition<ExprIndex, Index>("heap.expr", FilePartitionCache::ExprHeap);
    }

    Partition<AttrIndex, Index> File::attr_heap() const
    {
        return impl_->get_and_cache_partition<AttrIndex, Index>("heap.attr", FilePartitionCache::AttrHeap);
    }

    Partition<SyntaxIndex, Index> File::syntax_heap() const
    {
        return impl_->get_and_cache_partition<SyntaxIndex, Index>("heap.syn", FilePartitionCache::SyntaxHeap);
    }

    Partition<ModuleReference, Index> File::imported_modules() const
    {
        return impl_->get_and_cache_partition<ModuleReference, Index>("module.imported", FilePartitionCache::ImportedModules);
    }

    Partition<ModuleReference, Index> File::exported_modules() const
    {
        return impl_->get_and_cache_partition<ModuleReference, Index>("module.exported", FilePartitionCache::ExportedModules);
    }

    // ------------------------------------------------------------------------

    Partition<DeclIndex> File::deduction_guides() const
    {
        return impl_->get_and_cache_partition<DeclIndex, uint32_t>("name.guide", FilePartitionCache::DeductionGuides);
    }

    // ------------------------------------------------------------------------

    template<typename RetType, typename Value, typename Hasher>
    RetType get_value(DeclIndex declaration, std::unordered_map<DeclIndex, Value, Hasher> const & map)
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
