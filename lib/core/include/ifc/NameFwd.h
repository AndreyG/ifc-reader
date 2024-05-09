#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class NameSort;
    using NameIndex = AbstractReference<3, NameSort>;

    struct OperatorFunctionName;
    struct ConversionFunctionName;
    struct LiteralName;
    struct TemplateName;
    struct SpecializationName;
    struct SourceFileName;
    struct DeductionGuideName;
}