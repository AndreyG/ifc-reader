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

        static constexpr std::string_view PartitionName = "const.i64";
    };

    struct alignas(4) FPLiteral
    {
        std::byte raw_data[12];

        double value() const
        {
            return *reinterpret_cast<double const*>(raw_data);
        }

        static constexpr std::string_view PartitionName = "const.f64";
    };
}
