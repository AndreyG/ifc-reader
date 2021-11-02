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

    struct FPLiteral
    {
        double value;

        static constexpr std::string_view PartitionName = "const.f64";
    };
}
