#pragma once

#include <ranges>

namespace reflifc
{
    template<typename Range, typename Element>
    concept RangeOf = std::ranges::range<Range> && std::same_as<std::ranges::range_value_t<Range>, Element>;
}