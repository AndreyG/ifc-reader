#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class ExprSort;
    using ExprIndex = AbstractReference<6, ExprSort>;

    enum class StringSort : uint8_t;
    using StringIndex = AbstractReference<4, StringSort>;

    struct LiteralExpression;
    struct TupleExpression;
    struct TemplateId;
    struct NamedDecl;
    struct UnqualifiedId;
    struct TypeExpression;
    struct DyadExpression;
    struct SizeofExpression;
    struct AlignofExpression;
    struct PathExpression;
    struct PackedTemplateArguments;
    struct StringLiteral;
}
