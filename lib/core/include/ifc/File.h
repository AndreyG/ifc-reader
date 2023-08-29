#pragma once

#include "FileHeader.h"
#include "Partition.h"

#include "AttributeFwd.h"
#include "ChartFwd.h"
#include "ExpressionFwd.h"
#include "DeclarationFwd.h"
#include "Literal.h"
#include "NameFwd.h"
#include "SyntaxTreeFwd.h"
#include "TypeFwd.h"
#include "Module.h"

#include <memory>
#include <optional>
#include <span>

namespace ifc
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

#define DECLARE_PARTITION_GETTER(ElementType, IndexType, Property)  \
    public:                                                         \
    Partition<ElementType, IndexType> Property() const;        \
    private:                                                        \
        mutable std::optional<Partition<ElementType, IndexType>> cached_ ## Property ## _ ;

    // Declarations
    DECLARE_PARTITION_GETTER(Declaration, Index, declarations)

    DECLARE_PARTITION_GETTER(ScopeDeclaration, DeclIndex, scope_declarations)
    DECLARE_PARTITION_GETTER(TemplateDeclaration, DeclIndex, template_declarations)
    DECLARE_PARTITION_GETTER(PartialSpecialization, DeclIndex, partial_specializations)
    DECLARE_PARTITION_GETTER(Specialization, DeclIndex, specializations)
    DECLARE_PARTITION_GETTER(UsingDeclaration, DeclIndex, using_declarations)
    DECLARE_PARTITION_GETTER(Enumeration, DeclIndex, enumerations)
    DECLARE_PARTITION_GETTER(Enumerator, DeclIndex, enumerators)
    DECLARE_PARTITION_GETTER(AliasDeclaration, DeclIndex, alias_declarations)
    DECLARE_PARTITION_GETTER(DeclReference, DeclIndex, decl_references)
    DECLARE_PARTITION_GETTER(FunctionDeclaration, DeclIndex, functions)
    DECLARE_PARTITION_GETTER(MethodDeclaration, DeclIndex, methods)
    DECLARE_PARTITION_GETTER(Constructor, DeclIndex, constructors)
    DECLARE_PARTITION_GETTER(Destructor, DeclIndex, destructors)
    DECLARE_PARTITION_GETTER(VariableDeclaration, DeclIndex, variables)
    DECLARE_PARTITION_GETTER(ParameterDeclaration, DeclIndex, parameters)
    DECLARE_PARTITION_GETTER(FieldDeclaration, DeclIndex, fields)
    DECLARE_PARTITION_GETTER(FriendDeclaration, DeclIndex, friends)
    DECLARE_PARTITION_GETTER(Concept, DeclIndex, concepts)
    DECLARE_PARTITION_GETTER(IntrinsicDeclaration, DeclIndex,  intrinsic_declarations)

    DECLARE_PARTITION_GETTER(SpecializationForm, SpecFormIndex, specialization_forms)

    // Types
    DECLARE_PARTITION_GETTER(FundamentalType, TypeIndex, fundamental_types)
    DECLARE_PARTITION_GETTER(DesignatedType, TypeIndex, designated_types)
    DECLARE_PARTITION_GETTER(TorType, TypeIndex, tor_types)
    DECLARE_PARTITION_GETTER(SyntacticType, TypeIndex, syntactic_types)
    DECLARE_PARTITION_GETTER(ExpansionType, TypeIndex, expansion_types)
    DECLARE_PARTITION_GETTER(PointerType, TypeIndex, pointer_types)
    DECLARE_PARTITION_GETTER(FunctionType, TypeIndex, function_types)
    DECLARE_PARTITION_GETTER(MethodType, TypeIndex, method_types)
    DECLARE_PARTITION_GETTER(ArrayType, TypeIndex, array_types)
    DECLARE_PARTITION_GETTER(BaseType, TypeIndex, base_types)
    DECLARE_PARTITION_GETTER(TupleType, TypeIndex, tuple_types)
    DECLARE_PARTITION_GETTER(LvalueReference, TypeIndex, lvalue_references)
    DECLARE_PARTITION_GETTER(RvalueReference, TypeIndex, rvalue_references)
    DECLARE_PARTITION_GETTER(QualifiedType, TypeIndex, qualified_types)
    DECLARE_PARTITION_GETTER(ForallType, TypeIndex, forall_types)
    DECLARE_PARTITION_GETTER(SyntaxType, TypeIndex, syntax_types)
    DECLARE_PARTITION_GETTER(PlaceholderType, TypeIndex, placeholder_types)
    DECLARE_PARTITION_GETTER(TypenameType, TypeIndex, typename_types)
    DECLARE_PARTITION_GETTER(DecltypeType, TypeIndex, decltype_types)

    // Attributes
    DECLARE_PARTITION_GETTER(AttrBasic, AttrIndex, basic_attributes)
    DECLARE_PARTITION_GETTER(AttrScoped, AttrIndex, scoped_attributes)
    DECLARE_PARTITION_GETTER(AttrLabeled, AttrIndex, labeled_attributes)
    DECLARE_PARTITION_GETTER(AttrCalled, AttrIndex, called_attributes)
    DECLARE_PARTITION_GETTER(AttrExpanded, AttrIndex, expanded_attributes)
    DECLARE_PARTITION_GETTER(AttrFactored, AttrIndex, factored_attributes)
    DECLARE_PARTITION_GETTER(AttrElaborated, AttrIndex, elaborated_attributes)
    DECLARE_PARTITION_GETTER(AttrTuple, AttrIndex, tuple_attributes)

    // Expressions
    DECLARE_PARTITION_GETTER(LiteralExpression, ExprIndex, literal_expressions)
    DECLARE_PARTITION_GETTER(TypeExpression, ExprIndex, type_expressions)
    DECLARE_PARTITION_GETTER(NamedDecl, ExprIndex, decl_expressions)
    DECLARE_PARTITION_GETTER(UnqualifiedId, ExprIndex, unqualified_id_expressions)
    DECLARE_PARTITION_GETTER(TemplateId, ExprIndex, template_ids)
    DECLARE_PARTITION_GETTER(TemplateReference, ExprIndex, template_references)
    DECLARE_PARTITION_GETTER(MonadExpression, ExprIndex, monad_expressions)
    DECLARE_PARTITION_GETTER(DyadExpression, ExprIndex, dyad_expressions)
    DECLARE_PARTITION_GETTER(StringExpression, ExprIndex, string_expressions)
    DECLARE_PARTITION_GETTER(CallExpression, ExprIndex, call_expressions)
    DECLARE_PARTITION_GETTER(SizeofExpression, ExprIndex, sizeof_expressions)
    DECLARE_PARTITION_GETTER(AlignofExpression, ExprIndex, alignof_expressions)
    DECLARE_PARTITION_GETTER(RequiresExpression, ExprIndex, requires_expressions)
    DECLARE_PARTITION_GETTER(TupleExpression, ExprIndex, tuple_expressions)
    DECLARE_PARTITION_GETTER(PathExpression, ExprIndex, path_expressions)
    DECLARE_PARTITION_GETTER(ReadExpression, ExprIndex, read_expressions)
    DECLARE_PARTITION_GETTER(SyntaxTreeExpression, ExprIndex, syntax_tree_expressions)

    DECLARE_PARTITION_GETTER(ExpressionListExpression, ExprIndex, expression_lists)
    DECLARE_PARTITION_GETTER(QualifiedNameExpression, ExprIndex, qualified_name_expressions)
    DECLARE_PARTITION_GETTER(PackedTemplateArguments, ExprIndex, packed_template_arguments)
    DECLARE_PARTITION_GETTER(ProductValueTypeExpression, ExprIndex, product_value_type_expressions)

    DECLARE_PARTITION_GETTER(StringLiteral, StringIndex, string_literal_expressions)

    // Heaps
    DECLARE_PARTITION_GETTER(TypeIndex, Index, type_heap)
    DECLARE_PARTITION_GETTER(ExprIndex, Index, expr_heap)
    DECLARE_PARTITION_GETTER(AttrIndex, Index, attr_heap)
    DECLARE_PARTITION_GETTER(SyntaxIndex, Index, syntax_heap)

    // Names
    DECLARE_PARTITION_GETTER(OperatorFunctionName, NameIndex, operator_names)
    DECLARE_PARTITION_GETTER(SpecializationName,   NameIndex, specialization_names)
    DECLARE_PARTITION_GETTER(LiteralName,          NameIndex, literal_names)

    // Charts
    DECLARE_PARTITION_GETTER(ChartUnilevel,     ChartIndex, unilevel_charts)
    DECLARE_PARTITION_GETTER(ChartMultilevel,   ChartIndex, multilevel_charts)

    // Literals
    DECLARE_PARTITION_GETTER(IntegerLiteral,    LitIndex,   integer_literals)
    DECLARE_PARTITION_GETTER(FPLiteral,         LitIndex,   fp_literals)

    // Syntax Trees
    DECLARE_PARTITION_GETTER(SimpleTypeSpecifier, SyntaxIndex, simple_type_specifiers)
    DECLARE_PARTITION_GETTER(DecltypeSpecifier, SyntaxIndex, decltype_specifiers)
    DECLARE_PARTITION_GETTER(TypeSpecifierSeq, SyntaxIndex, type_specifier_seq_syntax_trees)
    DECLARE_PARTITION_GETTER(DeclSpecifierSeq, SyntaxIndex, decl_specifier_seq_syntax_trees)
    DECLARE_PARTITION_GETTER(TypeIdSyntax, SyntaxIndex, typeid_syntax_trees)
    DECLARE_PARTITION_GETTER(DeclaratorSyntax, SyntaxIndex, declarator_syntax_trees)
    DECLARE_PARTITION_GETTER(PointerDeclaratorSyntax, SyntaxIndex, pointer_declarator_syntax_trees)
    DECLARE_PARTITION_GETTER(FunctionDeclaratorSyntax, SyntaxIndex, function_declarator_syntax_trees)
    DECLARE_PARTITION_GETTER(ParameterDeclaratorSyntax, SyntaxIndex, parameter_declarator_syntax_trees)
    DECLARE_PARTITION_GETTER(ExpressionSyntax, SyntaxIndex, expression_syntax_trees)
    DECLARE_PARTITION_GETTER(RequiresClauseSyntax, SyntaxIndex, requires_clause_syntax_trees)
    DECLARE_PARTITION_GETTER(SimpleRequirementSyntax, SyntaxIndex, simple_requirement_syntax_trees)
    DECLARE_PARTITION_GETTER(TypeRequirementSyntax, SyntaxIndex, type_requirement_syntax_trees)
    DECLARE_PARTITION_GETTER(NestedRequirementSyntax, SyntaxIndex, nested_requirement_syntax_trees)
    DECLARE_PARTITION_GETTER(CompoundRequirementSyntax, SyntaxIndex, compound_requirement_syntax_trees)
    DECLARE_PARTITION_GETTER(RequirementBodySyntax, SyntaxIndex, requirement_body_syntax_trees)
    DECLARE_PARTITION_GETTER(TypeTemplateArgumentSyntax, SyntaxIndex, type_template_argument_syntax_trees)
    DECLARE_PARTITION_GETTER(TemplateArgumentListSyntax, SyntaxIndex, template_argument_list_syntax_trees)
    DECLARE_PARTITION_GETTER(TemplateIdSyntax, SyntaxIndex, templateid_syntax_trees)
    DECLARE_PARTITION_GETTER(TypeTraitIntrinsicSyntax, SyntaxIndex, type_trait_intrinsic_syntax_trees)
    DECLARE_PARTITION_GETTER(TupleSyntax, SyntaxIndex, tuple_syntax_trees)

    // Module References
    DECLARE_PARTITION_GETTER(ModuleReference, Index, imported_modules);
    DECLARE_PARTITION_GETTER(ModuleReference, Index, exported_modules);

    // Deducation guides
    Partition<DeclIndex> deduction_guides() const;

#undef DECLARE_PARTITION_GETTER

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
        template<typename T, typename Index>
        Partition<T, Index> get_partition_with_cache(std::optional<Partition<T, Index>> & cache) const;

        template<typename T, typename Index>
        Partition<T, Index> get_partition_with_cache(std::optional<Partition<T, Index>> & cache, std::string_view) const;

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };

    ScopeDeclaration const &        get_scope       (File const&, DeclIndex);
    Partition<Declaration, Index>   get_declarations(File const&, Sequence);
    Partition<ExprIndex, Index>     get_tuple_expression_elements(File const&, TupleExpression const&);

    Partition<ExprIndex, Index>     get_qualified_name_parts(File const& ifc, QualifiedNameExpression const&);
}
