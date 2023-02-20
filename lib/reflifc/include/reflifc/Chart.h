#pragma once

#include "reflifc/decl/Parameter.h"

#include "ViewOf.h"

#include <ifc/Chart.h>
#include <ifc/File.h>

namespace reflifc
{
    struct ChartUnilevel;

    struct Chart
    {
        Chart(ifc::File const& ifc, ifc::ChartIndex index)
            : ifc_(ifc),
              index_(index)
        {
        }

        ChartUnilevel as_unilevel() const;

        ifc::ChartSort sort() const { return index_.sort(); }

    private:
        ifc::File const& ifc_;
        ifc::ChartIndex index_;
    };

    struct Expression;

    struct ChartUnilevel
    {
        ChartUnilevel(ifc::File const& ifc, ifc::ChartUnilevel const& unilevel)
            : ifc_(ifc),
              unilevel_(unilevel)
        {
        }

        ViewOf<Parameter> auto parameters() const
        {
            return ifc_.parameters().slice(params_sequence())
                | std::views::transform([&ifc = ifc_] (ifc::ParameterDeclaration const & param) { return Parameter(ifc, param); });
        }

        ifc::Sequence params_sequence() const;

        bool        has_constraint()    const;
        Expression  constraint()        const;

    private:
        ifc::File const& ifc_;
        ifc::ChartUnilevel const& unilevel_;
    };
}
