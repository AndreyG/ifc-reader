#pragma once

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Chart;
    struct Type;

    struct ForallType
    {
        ForallType(ifc::File const& ifc, ifc::ForallType const& forall)
            : ifc_(ifc)
            , forall_(forall)
        {
        }

        Chart   chart()     const;
        Type    subject()   const;

    private:
        ifc::File const& ifc_;
        ifc::ForallType const& forall_;
    };
}
