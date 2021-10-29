#pragma once

#include <type_traits>

namespace ifc
{
    template<int N, typename Sort>
        requires std::is_enum_v<Sort>
    struct AbstractReference
    {
        // note: little endian
        uint32_t tag    : N;
        uint32_t index  : 32 - N;

        Sort sort() const
        {
            return static_cast<Sort>(tag);
        }
    };

    enum class DeclSort;
    enum class ExprSort;
    enum class NameSort;
    enum class TypeSort;

    using DeclIndex = AbstractReference<5, DeclSort>;
    using ExprIndex = AbstractReference<6, ExprSort>;
    using NameIndex = AbstractReference<3, NameSort>;
    using TypeIndex = AbstractReference<5, TypeSort>;

    enum class ChartSort;
    using ChartIndex = AbstractReference<2, ChartSort>;
}
