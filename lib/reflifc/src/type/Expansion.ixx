module;

#include <functional>

export module reflifc:ExpansionType;

import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    struct Type;

    export struct ExpansionType
    {
        ExpansionType(ifc::File const* ifc, ifc::ExpansionType const& expansion)
            : ifc_(ifc)
            , expansion_(&expansion)
        {
        }

        Type pack() const { return { ifc_, expansion_->pack }; }

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
    size_t operator()(reflifc::ExpansionType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.expansion_);
    }
};
