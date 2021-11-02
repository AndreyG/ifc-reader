#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class ExprSort;
    using ExprIndex = AbstractReference<6, ExprSort>;

    struct LiteralExpression;
    struct TupleExpression;
    struct TemplateId;
    struct NamedDecl;
    struct UnqualifiedId;
    struct TypeExpression;
    struct DyadExpression;
    struct SizeofExpression;
    struct AlignofExpression;
}
