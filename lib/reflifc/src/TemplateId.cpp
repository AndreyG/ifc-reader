﻿#include "reflifc/TemplateId.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"
#include "reflifc/Name.h"
#include "reflifc/TupleView.h"

#include <ifc/Expression.h>

namespace reflifc
{
    Expression TemplateId::primary() const
    {
        return Expression(ifc_, template_id_->primary);
    }

    TupleExpressionView TemplateId::arguments() const
    {
        return { ifc_, template_id_->arguments };
    }

    Declaration TemplateReference::member() const
    {
        return { ifc_, template_ref_->member };
    }

    Name TemplateReference::member_name() const
    {
        return { ifc_, template_ref_->member_name };
    }

    TupleExpressionView TemplateReference::arguments() const
    {
        return { ifc_, template_ref_->arguments };
    }
}
