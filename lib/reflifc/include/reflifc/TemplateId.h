#pragma once

#include <ifc/FileFwd.h>
#include <ifc/ExpressionFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Name;
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

    struct TemplateReference
    {
        TemplateReference(ifc::File const* ifc, ifc::TemplateReference const& template_ref)
            : ifc_(ifc)
            , template_ref_(&template_ref)
        {
        }

        Declaration         member()        const;
        Name                member_name()   const;
        TupleExpressionView arguments()     const;

    private:
        ifc::File const* ifc_;
        ifc::TemplateReference const* template_ref_;
    };
}