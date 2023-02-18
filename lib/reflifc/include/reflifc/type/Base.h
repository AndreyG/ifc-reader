#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Type.h>

#include "reflifc/Type.h"

namespace reflifc
{
    struct BaseType
    {
        BaseType(ifc::File const& ifc, ifc::BaseType base)
            : type(ifc, base.type)
            , access(base.access)
            , specifiers(base.specifiers)
        {
        }

        Type type;
        ifc::Access access;
        ifc::BaseType::Specifiers specifiers;
    };
}
