#pragma once

#include "SyntaxTreeFwd.h"

#include "CallingConvention.h"
#include "ExpressionFwd.h"
#include "Name.h"
#include "SourceLocation.h"
#include "TypeFwd.h"

namespace ifc
{
    enum class SyntaxSort
    {
        SimpleTypeSpecifier = 0x01,
        DecltypeSpecifier   = 0x02,
        TypeSpecifierSeq    = 0x04,
        DeclSpecifierSeq    = 0x05,
        TypeId              = 0x12,
        Declarator          = 0x14,
        PointerDeclarator   = 0x15,
        FunctionDeclarator  = 0x17,
        ParameterDeclarator = 0x19,
        Expression          = 0x3A,
        RequiresClause      = 0x3E,
        SimpleRequirement   = 0x3F,
        TypeRequirement     = 0x40,
        CompoundRequirement = 0x41,
        NestedRequirement   = 0x42,
        RequirementBody     = 0x43,
        TypeTemplateArgument= 0x46,
        TemplateArgumentList= 0x49,
        TemplateId          = 0x4A,
        TypeTraitIntrinsic  = 0x63,
        Tuple               = 0x64,
        // TODO
    };

    struct SimpleTypeSpecifier
    {
        TypeIndex type;
        ExprIndex expr;
        SourceLocation locus;

        PARTITION_NAME("syntax.simple-type-specifier");
        PARTITION_SORT(SyntaxSort::SimpleTypeSpecifier);
    };

    struct DecltypeSpecifier
    {
        ExprIndex argument;
        SourceLocation decltype_keyword, left_paren, right_paren;

        PARTITION_NAME("syntax.decltype-specifier");
        PARTITION_SORT(SyntaxSort::DecltypeSpecifier);
    };

    struct TypeSpecifierSeq
    {
        SyntaxIndex typename_;
        TypeIndex type;
        SourceLocation source;
        Qualifiers qualifiers;
        bool unshashed;

        PARTITION_NAME("syntax.type-specifier-seq");
        PARTITION_SORT(SyntaxSort::TypeSpecifierSeq);
    };

    enum class StorageClass : uint32_t {};

    struct DeclSpecifierSeq
    {
        TypeIndex type;
        SyntaxIndex typename_;
        SourceLocation source;
        StorageClass storage_class;
        SentenceIndex declspec;
        SyntaxIndex explicit_;
        Qualifiers qualifiers;

        PARTITION_NAME("syntax.decl-specifier-seq");
        PARTITION_SORT(SyntaxSort::DeclSpecifierSeq);
    };

    struct TypeIdSyntax
    {
        SyntaxIndex type_specifier;
        SyntaxIndex abstract_declarator;
        SourceLocation locus;

        PARTITION_NAME("syntax.type-id");
        PARTITION_SORT(SyntaxSort::TypeId);
    };

    struct DeclaratorSyntax
    {
        SyntaxIndex pointer;
        SyntaxIndex parenthesized;
        SyntaxIndex array_or_function;
        SyntaxIndex trailing_target;
        SyntaxIndex virtual_specifiers;
        ExprIndex name;
        SourceLocation ellipsis;
        SourceLocation locus;
        Qualifiers qualifiers;
        CallingConvention convention;
        bool callable;

        PARTITION_NAME("syntax.declarator");
        PARTITION_SORT(SyntaxSort::Declarator);
    };

    enum class PointerDeclaratorSort : uint8_t
    {
        None,
        Pointer,
        LvalueReference,
        RvalueReference,
        PointerToMember,
    };

    struct PointerDeclaratorSyntax
    {
        SyntaxIndex whole;
        SyntaxIndex next;
        SourceLocation locus;
        PointerDeclaratorSort sort;
        Qualifiers qualifiers;
        CallingConvention convention;
        bool callable;

        PARTITION_NAME("syntax.pointer-declarator");
        PARTITION_SORT(SyntaxSort::PointerDeclarator);
    };

    struct FunctionDeclaratorSyntax
    {
        SyntaxIndex parameters;
        SyntaxIndex eh_spec;
        SourceLocation left_paren, right_paren, ellipsis, ref;
        FunctionTypeTraits traits;

        PARTITION_NAME("syntax.function-declarator");
        PARTITION_SORT(SyntaxSort::FunctionDeclarator);
    };

    enum class ParameterSort : uint8_t;

    struct ParameterDeclaratorSyntax
    {
        SyntaxIndex decl_specifiers;
        SyntaxIndex declarator;
        ExprIndex default_;
        SourceLocation location;
        ParameterSort sort;

        PARTITION_NAME("syntax.parameter-declarator");
        PARTITION_SORT(SyntaxSort::ParameterDeclarator);
    };

    struct ExpressionSyntax
    {
        ExprIndex expression;

        PARTITION_NAME("syntax.expression");
        PARTITION_SORT(SyntaxSort::Expression);
    };

    struct RequiresClauseSyntax
    {
        ExprIndex condition;
        SourceLocation location;

        PARTITION_NAME("syntax.requires-clause");
        PARTITION_SORT(SyntaxSort::RequiresClause);
    };

    struct SimpleRequirementSyntax
    {
        ExprIndex condition;
        SourceLocation location;

        PARTITION_NAME("syntax.simple-requirement");
        PARTITION_SORT(SyntaxSort::SimpleRequirement);
    };

    struct TypeRequirementSyntax
    {
        ExprIndex type;
        SourceLocation location;

        PARTITION_NAME("syntax.type-requirement");
        PARTITION_SORT(SyntaxSort::TypeRequirement);
    };

    struct CompoundRequirementSyntax
    {
        ExprIndex condition;
        ExprIndex constraint;
        SourceLocation location;
        SourceLocation right_curly;
        SourceLocation noexcept_;

        PARTITION_NAME("syntax.compound-requirement");
        PARTITION_SORT(SyntaxSort::CompoundRequirement);
    };

    struct NestedRequirementSyntax
    {
        ExprIndex condition;
        SourceLocation location;

        PARTITION_NAME("syntax.nested-requirement");
        PARTITION_SORT(SyntaxSort::NestedRequirement);
    };

    struct RequirementBodySyntax
    {
        SyntaxIndex requirements;
        SourceLocation location;
        SourceLocation right_curly;

        PARTITION_NAME("syntax.requirement-body");
        PARTITION_SORT(SyntaxSort::RequirementBody);
    };

    struct TypeTemplateArgumentSyntax
    {
        SyntaxIndex argument;
        SourceLocation expander, comma;

        PARTITION_NAME("syntax.type-template-argument");
        PARTITION_SORT(SyntaxSort::TypeTemplateArgument);
    };

    struct TemplateArgumentListSyntax
    {
        SyntaxIndex arguments;
        SourceLocation lt, gt;

        PARTITION_NAME("syntax.template-argument-list");
        PARTITION_SORT(SyntaxSort::TemplateArgumentList);
    };

    struct TemplateIdSyntax
    {
        SyntaxIndex name;
        ExprIndex symbol;
        SyntaxIndex arguments;
        SourceLocation locus, template_;

        PARTITION_NAME("syntax.template-id");
        PARTITION_SORT(SyntaxSort::TemplateId);
    };

    struct TypeTraitIntrinsicSyntax
    {
        SyntaxIndex arguments;
        SourceLocation location;
        Operator intrinsic;

        PARTITION_NAME("syntax.type-trait-intrinsic");
        PARTITION_SORT(SyntaxSort::TypeTraitIntrinsic);
    };

    struct TupleSyntax : Sequence
    {
        PARTITION_NAME("syntax.tuple");
        PARTITION_SORT(SyntaxSort::Tuple);
    };
}
