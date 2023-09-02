#pragma once

#include "reflifc/Type.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

#include <functional>

namespace reflifc
{
    struct AlignofExpression
    {
        AlignofExpression(ifc::File const* ifc, ifc::AlignofExpression const& expr);

        auto operator<=>(AlignofExpression const& other) const = default;

        Type operand;
    };
}

template<>
struct std::hash<reflifc::AlignofExpression>
{
    size_t operator()(reflifc::AlignofExpression const& object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.operand);
    }
};
