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
        // TODO
    };

    struct SimpleTypeSpecifier
    {
        TypeIndex type;
        ExprIndex expr;
        SourceLocation locus;

        static constexpr std::string_view PartitionName = "syntax.simple-type-specifier";
    };

    struct TypeSpecifierSeq
    {
        SyntaxIndex typename_;
        TypeIndex type;
        SourceLocation source;
        Qualifiers qualifiers;
        bool unshashed;

        static constexpr std::string_view PartitionName = "syntax.type-specifier-seq";
    };

    struct TypeIdSyntax
    {
        SyntaxIndex type_specifier;
        SyntaxIndex abstract_declarator;
        SourceLocation locus;

        static constexpr std::string_view PartitionName = "syntax.type-id";
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

        static constexpr std::string_view PartitionName = "syntax.declarator";
    };

    enum class PointerDeclaratorSort : uint8_t;

    struct PointerDeclaratorSyntax
    {
        SyntaxIndex whole;
        SyntaxIndex next;
        SourceLocation locus;
        PointerDeclaratorSort sort;
        Qualifiers qualifiers;
        CallingConvention convention;
        bool callable;

        static constexpr std::string_view PartitionName = "syntax.pointer-declarator";
    };

    struct ExpressionSyntax
    {
        ExprIndex expression;

        static constexpr std::string_view PartitionName = "syntax.expression";
    };
}
