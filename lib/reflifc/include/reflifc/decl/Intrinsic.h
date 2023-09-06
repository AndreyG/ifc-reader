#pragma once

#include "reflifc/Declaration.h"
#include "reflifc/Type.h"

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

        ifc::File const* containing_file() const { return ifc_; }

    private:
        ifc::File const* ifc_;
        ifc::IntrinsicDeclaration const* intrinsic_;
    };
}
