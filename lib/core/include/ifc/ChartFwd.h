#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class ChartSort;
    using ChartIndex = AbstractReference<2, ChartSort>;

    struct ChartUnilevel;
    struct ChartMultilevel;
}
