#pragma once

#include <cstdint>

namespace ifc
{
    enum class CallingConvention : std::uint8_t
    {
        Cdecl,
        Fast,
        Std,
        This,
        Clr,
        Vector,
        Eabi,
    };
}
