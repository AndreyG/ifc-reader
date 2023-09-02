#pragma once

#include "reflifc/Type.h"

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

#include <functional>

namespace reflifc
{
    struct SizeofExpression
    {
        SizeofExpression(ifc::File const* ifc, ifc::SizeofExpression const& expr);

        auto operator<=>(SizeofExpression const& other) const = default;

        Type operand;
    };
}

template<>
struct std::hash<reflifc::SizeofExpression>
{
    size_t operator()(reflifc::SizeofExpression const& object) const noexcept
    {
        return std::hash<reflifc::Type>{}(object.operand);
    }
};
