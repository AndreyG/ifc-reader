export module ifc.CallingConvention;

import ifc.common_types;

namespace ifc
{
    export enum class CallingConvention : uint8_t
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
