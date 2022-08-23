#pragma once

#include "SyntaxTreeFwd.h"

#include "ExpressionFwd.h"

#include <string_view>

namespace ifc
{
    enum class SyntaxSort
    {
        SimpleTypeSpecifier = 0x01,
        TypeSpecifierSeq    = 0x04,
        TypeId              = 0x12,
        Declarator          = 0x14,
        PointerDeclarator   = 0x15,
        Expression          = 0x3A,
        TypeTemplateArgument= 0x46,
        TemplateArgumentList= 0x49,
        TemplateId          = 0x4A,
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

    struct ExpressionSyntax
    {
        ExprIndex expression;

        PARTITION_NAME("syntax.expression");
        PARTITION_SORT(SyntaxSort::Expression);
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

    struct TupleSyntax : Sequence
    {
        PARTITION_NAME("syntax.tuple");
        PARTITION_SORT(SyntaxSort::Tuple);
    };
}
