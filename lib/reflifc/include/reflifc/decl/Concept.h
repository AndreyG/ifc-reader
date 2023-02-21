#pragma once

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Chart;

    struct Concept
    {
        Concept(ifc::File const* ifc, ifc::Concept const& c)
            : ifc_(ifc)
            , c_(&c)
        {
        }

        char const* name()          const;
        Expression  definition()    const;
        Chart       chart()         const;
        Declaration home_scope()    const;

    private:
        ifc::File const* ifc_;
        ifc::Concept const* c_;
    };
}
