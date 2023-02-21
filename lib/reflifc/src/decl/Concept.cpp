#include "reflifc/decl/Concept.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"
#include "reflifc/Chart.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

namespace reflifc
{
    char const* Concept::name() const
    {
        return ifc_->get_string(c_->name);
    }

    Expression Concept::definition() const
    {
        return { ifc_, c_->constraint };
    }

    Chart Concept::chart() const
    {
        return { ifc_, c_->chart };
    }

    Declaration Concept::home_scope() const
    {
        return { ifc_, c_->home_scope };
    }
}
