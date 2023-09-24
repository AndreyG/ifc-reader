export module ifc.Module;

import ifc.common_types;

namespace ifc
{
    export struct ModuleReference
    {
        TextOffset owner;
        TextOffset partition;
    };
}
