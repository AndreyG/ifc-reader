#pragma once

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

    private:
        ifc::File const* ifc_;
        ifc::ExpansionType const* expansion_;
    };
}
