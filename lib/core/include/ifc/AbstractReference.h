#pragma once

#include <type_traits>
#include <cstdint>
#include <utility>

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

        auto operator<=>(const AbstractReference& rhs) const = default;
    };
}

namespace std
{
    template<int N, typename Sort>
        requires std::is_enum_v<Sort>
    struct hash<ifc::AbstractReference<N, Sort>>
    {
        std::size_t operator()(ifc::AbstractReference<N, Sort> const& s) const noexcept
        {
            return std::hash<uint32_t>{}((uint32_t&)s);
        }
    };
}