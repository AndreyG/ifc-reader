#pragma once

#include "reflifc/Declaration.h"
#include "reflifc/Type.h"
#include "reflifc/HashCombine.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

namespace reflifc
{
    struct IntrinsicDeclaration
    {
        IntrinsicDeclaration(ifc::File const* ifc, ifc::IntrinsicDeclaration const& intrinsic)
            : ifc_(ifc)
            , intrinsic_(&intrinsic)
        {
        }

        const char* name()          const { return ifc_->get_string(intrinsic_->name); }
        Type        type()          const { return { ifc_, intrinsic_->type }; }
        Declaration home_scope()    const { return { ifc_, intrinsic_->home_scope }; }

        auto operator<=>(IntrinsicDeclaration const& other) const = default;

    private:
        friend std::hash<IntrinsicDeclaration>;

        ifc::File const* ifc_;
        ifc::IntrinsicDeclaration const* intrinsic_;
    };
}

template<>
struct std::hash<reflifc::IntrinsicDeclaration>
{
    size_t operator()(reflifc::IntrinsicDeclaration const& intrinsic) const noexcept
    {
        return reflifc::hash_combine(0, intrinsic.ifc_, intrinsic.intrinsic_);
    }
};
