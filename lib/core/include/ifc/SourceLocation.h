#pragma once

#include <cstdint>

namespace ifc
{
    using std::uint32_t;

    enum class LineIndex : uint32_t {};

    enum class Column : uint32_t {};

    struct SourceLocation
    {
        LineIndex   line;
        Column      column;
    };
}
