#pragma once

#include <ifc/Declaration.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Type;
    struct Chart;

    struct Parameter
    {
        Parameter(ifc::File const& ifc, ifc::ParameterDeclaration const& param)
            : ifc_(ifc)
            , param_(param)
        {
        }

        const char* name() const;
        Type        type() const;

        Chart template_parameters() const;

        ifc::ParameterSort sort() const { return param_.sort; }

    private:
        ifc::File const & ifc_;
        ifc::ParameterDeclaration const& param_;
    };
}
