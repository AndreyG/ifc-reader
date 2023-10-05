module;

#include <cassert>
#include <compare>

export module reflifc.Literal;

import ifc;
import ifc.Literal;

namespace reflifc
{
    export struct Literal
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
        ifc::File const* ifc_;
        ifc::LitIndex index_;
    };
}
