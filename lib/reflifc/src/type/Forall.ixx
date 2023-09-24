module;

#include <functional>

export module reflifc:ForallType;

import :Chart;
import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    struct Chart;
    struct Type;

    export struct ForallType
    {
        ForallType(ifc::File const* ifc, ifc::ForallType const& forall)
            : ifc_(ifc)
            , forall_(&forall)
        {
        }

        Chart   chart()     const { return { ifc_, forall_->chart }; }
        Type    subject()   const { return { ifc_, forall_->subject }; }

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
