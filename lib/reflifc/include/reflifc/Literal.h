#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Literal.h>

namespace reflifc
{
    struct Literal
    {
        Literal(ifc::File const& ifc, ifc::LitIndex index)
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

    private:
        ifc::File const& ifc_;
        ifc::LitIndex index_;
    };
}
