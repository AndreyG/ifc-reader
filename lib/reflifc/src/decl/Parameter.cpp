#include "reflifc/decl/Parameter.h"

#include "reflifc/Chart.h"
#include "reflifc/Type.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

#include "ifc/Type.h"
#include "reflifc/type/Forall.h"

namespace reflifc
{
    const char* Parameter::name() const
    {
        return ifc_.get_string(param_.name);
    }

    Type Parameter::type() const
    {
        return { ifc_, param_.type };
    }

    Chart Parameter::template_parameters() const
    {
        auto forall_type = type().as_forall();
        assert(forall_type.subject().as_fundamental().basis == ifc::TypeBasis::Typename);
        return forall_type.chart();
    }
}
