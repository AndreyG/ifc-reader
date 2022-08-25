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
        uint16_t tag    : 4;
        uint16_t index  : 12;

        enum class Sort
        {
            Niladic = 0x00,
            Monadic = 0x01,
            Dyadic  = 0x02,
            Triadic = 0x03,
            Storage = 0x0E,
            Variadic= 0x0F,
        };

        Sort sort() const
        {
            return static_cast<Sort>(tag);
        }
    };

    static_assert(sizeof(Operator) == sizeof(uint16_t));

    enum class MonadicOperatorSort
    {
        MsvcIsNothrowDestructible = 0x41B,
        // TODO
    };

    enum class DyadicOperatorSort
    {
        MsvcIsConvertibleTo = 0x40B,
        // TODO
    };

    enum class VariadicOperatorSort
    {
        MsvcIsConstructible = 0x402,
        // TODO
    };

    struct OperatorFunctionName
    {
        TextOffset encoded;
        Operator operator_;

        PARTITION_NAME("name.operator");
        PARTITION_SORT(NameSort::Operator);
    };
}
