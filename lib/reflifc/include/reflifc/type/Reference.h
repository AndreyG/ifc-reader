#pragma once

#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    struct LvalueReference
    {
        LvalueReference(ifc::File const* ifc, ifc::LvalueReference ref)
            : referee(ifc, ref.referee)
        {
        }

        Type referee;
    };

    struct RvalueReference
    {
        RvalueReference(ifc::File const* ifc, ifc::RvalueReference ref)
            : referee(ifc, ref.referee)
        {
        }

        Type referee;
    };
    
}
