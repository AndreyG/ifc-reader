#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Chart;
    struct Type;

    struct ForallType
    {
        ForallType(ifc::File const* ifc, ifc::ForallType const& forall)
            : ifc_(ifc)
            , forall_(&forall)
        {
        }

        Chart   chart()     const;
        Type    subject()   const;

        auto operator<=>(ForallType const& other) const = default;

    private:
        friend std::hash<ForallType>;

        ifc::File const* ifc_;
        ifc::ForallType const* forall_;
    };
}

template<>
struct std::hash<reflifc::ForallType>
{
    size_t operator()(reflifc::ForallType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.forall_);
    }
};
