#pragma once

#include "HashCombine.h"

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

        auto operator<=>(TemplateId const& other) const = default;

    private:
        friend std::hash<TemplateId>;

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

        auto operator<=>(TemplateReference const& other) const = default;

    private:
        friend std::hash<TemplateReference>;

        ifc::File const* ifc_;
        ifc::TemplateReference const* template_ref_;
    };
}

template<>
struct std::hash<reflifc::TemplateId>
{
    size_t operator()(reflifc::TemplateId object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.template_id_);
    }
};

template<>
struct std::hash<reflifc::TemplateReference>
{
    size_t operator()(reflifc::TemplateReference object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.template_ref_);
    }
};
