#pragma once

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;

    struct PlaceholderType
    {
        PlaceholderType(ifc::File const& ifc, ifc::PlaceholderType const& placeholder)
            : ifc_(ifc),
              placeholder_(placeholder)
        {
        }

        ifc::TypeBasis basis() const;
        Type elaboration() const;

    private:
        ifc::File const& ifc_;
        ifc::PlaceholderType const& placeholder_;
    };
}
