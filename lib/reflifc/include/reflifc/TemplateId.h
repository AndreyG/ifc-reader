#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Expression;
    struct TupleExpressionView;

    struct TemplateId
    {
        TemplateId(ifc::File const* ifc, ifc::TemplateId const& template_id)
            : ifc_(ifc)
            , template_id_(&template_id)
        {
        }

        Expression primary() const;

        TupleExpressionView arguments() const;

    private:
        ifc::File const* ifc_;
        ifc::TemplateId const* template_id_;
    };
}