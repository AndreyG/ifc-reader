#pragma once

#include <type_traits>
#include <cstdint>
#include <functional>

namespace ifc
{
    template<int N, typename _Sort>
        requires std::is_enum_v<_Sort>
    struct AbstractReference
    {
        using Sort = _Sort;

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

        bool operator==(const AbstractReference& rhs) const = default;
    };
}

template<int N, typename Sort>
	requires std::is_enum_v<Sort>
struct std::hash<ifc::AbstractReference<N, Sort>>
{
	std::size_t operator()(ifc::AbstractReference<N, Sort> s) const noexcept
	{
		return std::hash<uint32_t>{}(reinterpret_cast<uint32_t&>(s));
	}
};
