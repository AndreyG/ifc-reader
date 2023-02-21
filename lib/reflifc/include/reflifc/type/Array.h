#pragma once

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;
    struct Expression;

    struct ArrayType
    {
        ArrayType(ifc::File const* ifc, ifc::ArrayType const& array)
            : ifc_(ifc)
            , array_(&array)
        {
        }

        Type        element() const;
        Expression  extent() const;

    private:
        ifc::File const* ifc_;
        ifc::ArrayType const* array_;
    };

    std::uint32_t extent_value(ArrayType);
}
