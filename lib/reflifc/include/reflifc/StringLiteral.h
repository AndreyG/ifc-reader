#pragma once

#include "HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct StringLiteral
    {
        StringLiteral(ifc::File const* file, ifc::StringLiteral literal)
            : ifc_(file)
            , literal_(literal)
        {
        }

        std::string_view value() const;

        auto operator<=>(StringLiteral const& other) const = default;

    private:
        friend std::hash<StringLiteral>;

        ifc::File const* ifc_;
        ifc::StringLiteral literal_;
    };
}

template<>
struct std::hash<reflifc::StringLiteral>
{
    size_t operator()(reflifc::StringLiteral const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.literal_.start, object.literal_.length, object.literal_.suffix);
    }
};
