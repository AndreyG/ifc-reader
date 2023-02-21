#pragma once

#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    struct PointerType
    {
        PointerType(ifc::File const* ifc, ifc::PointerType pointer)
            : pointee(ifc, pointer.pointee)
        {
        }

        Type pointee;
    };
}
