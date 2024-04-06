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
        Partition<SubobjectValueExpression, ExprIndex>      suboject_value_expressions() const;

        Partition<StringLiteral, StringIndex> string_literal_expressions() const;

        // Heaps
        Partition<TypeIndex, Index>     type_heap() const;
        Partition<ExprIndex, Index>     expr_heap() const;
        Partition<AttrIndex, Index>     attr_heap() const;
        Partition<SyntaxIndex, Index>   syntax_heap() const;

        // Names
        Partition<OperatorFunctionName, NameIndex>      operator_names() const;
        Partition<ConversionFunctionName, NameIndex>    conversion_function_names() const;
        Partition<LiteralName, NameIndex>               literal_names() const;
        Partition<TemplateName, NameIndex>              template_names() const;
        Partition<SpecializationName, NameIndex>        specialization_names() const;
        Partition<SourceFileName, NameIndex>            source_file_names() const;
        Partition<DeductionGuideName, NameIndex>        deduction_guide_names() const;

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
}
