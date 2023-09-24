export module ifc:Chart;

import :ChartIndex;
import :ExprIndex;

import ifc.common_types;

#include "partition_defines.h"

export namespace ifc
{
    struct ChartUnilevel : Sequence
    {
        ExprIndex constraint;

        PARTITION_NAME("chart.unilevel");
        PARTITION_SORT(ChartSort::Unilevel);
    };

    struct ChartMultilevel
    {

        PARTITION_NAME("chart.multilevel");
        PARTITION_SORT(ChartSort::Multilevel);
    };
}
