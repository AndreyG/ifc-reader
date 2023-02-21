#pragma once

#include <ifc/FileFwd.h>
#include <ifc/Expression.h>

namespace reflifc
{
    struct StringLiteral
    {
        StringLiteral(ifc::File const* file, ifc::StringLiteral literal)
            : ifc_(file)
            , literal_(literal)
        {
        }

        std::string_view value() const;

    private:
        ifc::File const* ifc_;
        ifc::StringLiteral literal_;
    };
}
