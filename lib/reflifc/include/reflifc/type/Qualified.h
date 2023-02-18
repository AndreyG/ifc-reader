#pragma once

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;

    struct QualifiedType
    {
        QualifiedType(ifc::File const& ifc, ifc::QualifiedType const& qualified)
            : ifc_(ifc),
              qualified_(qualified)
        {
        }

        Type            unqualified()   const;
        ifc::Qualifiers qualifiers()    const;

    private:
        ifc::File const& ifc_;
        ifc::QualifiedType const& qualified_;
    };
}
