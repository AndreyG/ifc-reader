#include "reflifc/type/Forall.h"

#include "reflifc/Chart.h"
#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    Chart ForallType::chart() const
    {
        return { ifc_, forall_.chart };
    }

    Type ForallType::subject() const
    {
        return { ifc_, forall_.subject };
    }
}
