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
        TemplateId          = 0x4A,
        // TODO
    };

    struct SimpleTypeSpecifier
    {
        TypeIndex type;
        ExprIndex expr;
        SourceLocation locus;

        PARTITION_NAME("syntax.simple-type-specifier");
    };

    struct TypeSpecifierSeq
    {
        SyntaxIndex typename_;
        TypeIndex type;
        SourceLocation source;
        Qualifiers qualifiers;
        bool unshashed;

        PARTITION_NAME("syntax.type-specifier-seq");
    };

    struct TypeIdSyntax
    {
        SyntaxIndex type_specifier;
        SyntaxIndex abstract_declarator;
        SourceLocation locus;

        PARTITION_NAME("syntax.type-id");
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
    };

    struct ExpressionSyntax
    {
        ExprIndex expression;

        PARTITION_NAME("syntax.expression");
    };

    struct TemplateIdSyntax
    {
        SyntaxIndex name;
        ExprIndex symbol;
        SyntaxIndex arguments;
        SourceLocation locus, template_;

        PARTITION_NAME("syntax.template-id");
    };
}
