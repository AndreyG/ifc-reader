#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class ExprSort;
    using ExprIndex = AbstractReference<6, ExprSort>;

    struct TupleExpression;
    struct TemplateId;
    struct NamedDecl;
    struct TypeExpression;
    struct DyadExpression;
    struct SizeofExpression;
    struct AlignofExpression;
}
