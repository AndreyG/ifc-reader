#pragma once

#include "ExpressionFwd.h"

#include "SourceLocation.h"

#include "common_types.h"

#include <string_view>

namespace ifc
{
    enum class ExprSort
    {
        Type                = 0x04,
        NamedDecl           = 0x05,
        TemplateId          = 0x07,
        HierarchyConversion = 0x29,
        Tuple               = 0x33,
        // TODO
    };

    struct NamedDecl
    {
        SourceLocation source;
        TypeIndex type;
        DeclIndex resolution;

        static constexpr std::string_view PartitionName = "expr.decl";
    };

    struct TemplateId
    {
        SourceLocation source;
        TypeIndex type;
        ExprIndex primary;
        ExprIndex arguments;

        static constexpr std::string_view PartitionName = "expr.template-id";
    };

    struct TupleExpression
    {
        SourceLocation locus;
        TypeIndex type;
        Sequence seq;

        static constexpr std::string_view PartitionName = "expr.tuple";
    };

    struct TypeExpression
    {
        SourceLocation locus;
        TypeIndex type;
        TypeIndex denotation;

        static constexpr std::string_view PartitionName = "expr.type";
    };
}
