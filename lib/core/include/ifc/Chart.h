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

        static constexpr std::string_view PartitionName = "chart.unilevel";
    };

    struct ChartMultilevel
    {

        static constexpr std::string_view PartitionName = "chart.multilevel";
    };
}
