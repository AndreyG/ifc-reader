module;

#include <ranges>

export module reflifc.ViewOf;

namespace reflifc
{
    export template<typename Range, typename Element>
    concept ViewOf = std::ranges::view<Range> && std::same_as<std::ranges::range_value_t<Range>, Element>;
}