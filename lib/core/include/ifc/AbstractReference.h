#pragma once

#include <type_traits>
#include <cstdint>

namespace ifc
{
    template<int N, typename Sort>
        requires std::is_enum_v<Sort>
    struct AbstractReference
    {
        uint32_t tag    : N;
        uint32_t index  : 32 - N;

        Sort sort() const
        {
            return static_cast<Sort>(tag);
        }

        bool is_null() const
        {
            return tag == 0 && index == 0;
        }
    };
}
