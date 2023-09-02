#pragma once

#include "HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/Literal.h>

namespace reflifc
{
    struct Literal
    {
        Literal(ifc::File const* ifc, ifc::LitIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        bool is_null() const { return index_.is_null(); }

        std::uint32_t int_value() const
        {
            assert(sort() == ifc::LiteralSort::Immediate);
            return index_.index;
        }

        ifc::LiteralSort sort() const { return index_.sort(); }

        auto operator<=>(Literal const& other) const = default;

    private:
        friend std::hash<Literal>;

        ifc::File const* ifc_;
        ifc::LitIndex index_;
    };
}

template<>
struct std::hash<reflifc::Literal>
{
    size_t operator()(reflifc::Literal const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.index_);
    }
};
