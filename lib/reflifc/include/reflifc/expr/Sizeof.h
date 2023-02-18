#pragma once

#include "reflifc/Type.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct SizeofExpression
    {
        SizeofExpression(ifc::File const& ifc, ifc::SizeofExpression const& expr);

        Type operand;
    };
}
