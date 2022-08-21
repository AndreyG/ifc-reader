#pragma once

#include "NameFwd.h"

#include "common_types.h"

#include <string_view>

namespace ifc
{
    enum class NameSort
    {
        Identifier      = 0x00,
        Operator        = 0x01,
        Conversion      = 0x02,
        Literal         = 0x03,
        Template        = 0x04,
        Specialization  = 0x05,
        SourceFile      = 0x06,
        Guide           = 0x07,
    };

    struct Operator
    {
        uint16_t sort   : 4;
        uint16_t index  : 12;
    };

    static_assert(sizeof(Operator) == sizeof(uint16_t));

    struct OperatorFunctionName
    {
        TextOffset encoded;
        Operator operator_;

        PARTITION_NAME("name.operator");
    };
}
