#pragma once

#include <cstdint>
#include <cstddef>
#include <string_view>

namespace ifc
{
    using std::uint8_t;
    using std::uint16_t;
    using std::uint32_t;

    enum class TextOffset : uint32_t { };

    inline bool is_null(TextOffset offset)
    {
        return offset == TextOffset{0};
    }

    enum class ByteOffset : uint32_t {};

    enum class Cardinality : uint32_t {};

    inline size_t raw_count(Cardinality c)
    {
        return static_cast<size_t>(c);
    }

    enum class EntitySize : uint32_t {};

    enum class Index : uint32_t {};

    inline Index operator+(Index start, size_t offset)
    {
        return Index { static_cast<uint32_t>(start) + static_cast<uint32_t>(offset) };
    }

    enum class SentenceIndex : uint32_t {};

    enum class WordIndex : uint32_t { };

    struct Sequence
    {
        Index start;
        Cardinality cardinality;
    };

#define PARTITION_NAME(value) static constexpr std::string_view PartitionName = value

#define PARTITION_SORT(value) static constexpr auto Sort = value

}
