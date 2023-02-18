#include "reflifc/type/Array.h"

#include "reflifc/Expression.h"
#include "reflifc/Type.h"
#include "reflifc/Literal.h"

#include <ifc/Type.h>

namespace reflifc
{
    Type ArrayType::element() const
    {
        return { ifc_, array_.element };
    }

    Expression ArrayType::extent() const
    {
        return { ifc_, array_.extent };
    }

    std::uint32_t extent_value(ArrayType array)
    {
        return array.extent().as_literal().int_value();
    }
}
