module;

#include <cassert>
#include <cstdint>

export module ifc.common_types;

export namespace ifc
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

    inline std::size_t raw_count(Cardinality c)
    {
        return static_cast<std::size_t>(c);
    }

    enum class EntitySize : uint32_t {};

    enum class Index : uint32_t {};

    inline Index operator+(Index start, std::size_t offset)
    {
        return Index { static_cast<uint32_t>(start) + static_cast<uint32_t>(offset) };
    }

    enum class SentenceIndex : uint32_t {};

    enum class WordIndex : uint32_t { };

    struct Sequence
    {
        Index start;
        Cardinality cardinality;

        Index last() const
        {
            return start + (raw_count(cardinality) - 1);
        }

        Sequence shift(std::size_t n) const
        {
            return { start + n, cardinality };
        }

        Sequence drop(uint32_t n) const
        {
            const auto size = static_cast<uint32_t>(cardinality);
            assert(n <= size);
            return { start + n, static_cast<Cardinality>(size - n) };
        }
    };
}
