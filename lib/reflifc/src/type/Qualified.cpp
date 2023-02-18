#include "reflifc/type/Qualified.h"

#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    Type QualifiedType::unqualified() const
    {
        return { ifc_, qualified_.unqualified };
    }

    ifc::Qualifiers QualifiedType::qualifiers() const
    {
        return qualified_.qualifiers;
    }
}
