#pragma once

#include "common_types.h"

namespace ifc
{
    struct ModuleReference
    {
        TextOffset owner;
        TextOffset partition;
    };
}
