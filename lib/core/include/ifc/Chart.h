#pragma once

#include "ChartFwd.h"

#include "ExpressionFwd.h"

#include "common_types.h"

namespace ifc
{
    enum class ChartSort
    {
        None        = 0x00,
        Unilevel    = 0x01,
        Multilevel  = 0x02,
    };

    struct ChartUnilevel : Sequence
    {
        ExprIndex constraint;

        PARTITION_NAME("chart.unilevel");
    };

    struct ChartMultilevel
    {

        PARTITION_NAME("chart.multilevel");
    };
}
