#pragma once

#include "reflifc/Type.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct AlignofExpression
    {
        AlignofExpression(ifc::File const* ifc, ifc::AlignofExpression const& expr);

        Type operand;
    };
}
