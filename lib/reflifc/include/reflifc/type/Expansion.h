#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;

    struct ExpansionType
    {
        ExpansionType(ifc::File const* ifc, ifc::ExpansionType const& expansion)
            : ifc_(ifc)
            , expansion_(&expansion)
        {
        }

        Type pack() const;

        auto operator<=>(ExpansionType const& other) const = default;

    private:
        friend std::hash<ExpansionType>;

        ifc::File const* ifc_;
        ifc::ExpansionType const* expansion_;
    };
}

template<>
struct std::hash<reflifc::ExpansionType>
{
    size_t operator()(reflifc::ExpansionType const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expansion_);
    }
};
