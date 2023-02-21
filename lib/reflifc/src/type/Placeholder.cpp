#include "reflifc/type/Placeholder.h"

#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    ifc::TypeBasis PlaceholderType::basis() const
    {
        return placeholder_->basis;
    }

    Type PlaceholderType::elaboration() const
    {
        return { ifc_, placeholder_->elaboration };
    }
}
