#include "reflifc/type/Expansion.h"

#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    Type ExpansionType::pack() const
    {
        return { ifc_, expansion_.pack };
    }
}
