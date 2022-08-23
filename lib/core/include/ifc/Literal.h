#pragma once

#include "AbstractReference.h"

#include <cstdint>
#include <string_view>

namespace ifc
{
    enum class LiteralSort
    {
        Immediate,
        Integer,
        FloatingPoint,
    };

    using LitIndex = AbstractReference<2, LiteralSort>;

    struct IntegerLiteral
    {
        std::uint64_t value;

        PARTITION_NAME("const.i64");
        PARTITION_SORT(LiteralSort::Integer);
    };

    struct alignas(4) FPLiteral
    {
        std::byte raw_data[12];

        double value() const
        {
            return *reinterpret_cast<double const*>(raw_data);
        }

        PARTITION_NAME("const.f64");
        PARTITION_SORT(LiteralSort::FloatingPoint);
    };
}
