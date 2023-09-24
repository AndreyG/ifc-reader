module;

#include <cassert>
#include <functional>

export module reflifc.Literal;

import reflifc.HashCombine;

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
        friend std::hash<Literal>;

        ifc::File const* ifc_;
        ifc::LitIndex index_;
    };
}

template<>
struct std::hash<reflifc::Literal>
{
    size_t operator()(reflifc::Literal object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.index_);
    }
};
