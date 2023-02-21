#pragma once

#include "reflifc/Expression.h"
#include "reflifc/Literal.h"

#include <ifc/DeclarationFwd.h>

namespace reflifc
{
    struct Enumerator
    {
        Enumerator(ifc::File const* ifc, ifc::Enumerator const& enumerator)
            : ifc_(ifc)
            , enumerator_(&enumerator)
        {
        }

        const char* name() const;

        Expression value() const;

    private:
        ifc::File const* ifc_;
        ifc::Enumerator const* enumerator_;
    };

    inline auto int_value(Enumerator enumerator)
    {
        return enumerator.value().as_literal().int_value();
    }
}
