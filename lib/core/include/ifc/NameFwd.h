#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class NameSort;
    using NameIndex = AbstractReference<3, NameSort>;

    struct OperatorFunctionName;
    struct SpecializationName;
    struct LiteralName;
}