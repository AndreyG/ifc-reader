#pragma once

#include "AbstractReference.h"

#include "common_types.h"

#include <cassert>
#include <concepts>
#include <ranges>

namespace ifc
{
    struct PartitionSummary
    {
        TextOffset name;
        ByteOffset offset;
        Cardinality cardinality;
        EntitySize entry_size;

        size_t size_bytes() const
        {
            return raw_count(cardinality) * static_cast<size_t>(entry_size);
        }
    };

    template<typename Index>
    Index get_raw_index(Index index)
    {
        return index;
    }

    template<int N, typename Sort>
    uint32_t get_raw_index(AbstractReference<N, Sort> ref)
    {
        return ref.index;
    }

    template<typename T, typename Index>
    concept CanValidateIndexSort = requires(Index index)
    {
        { T::Sort };
        { index.sort() };
    };

    template<typename T, typename Index = uint32_t>
    class Partition : public std::ranges::view_base
    {
    public:
        T const & operator[] (Index index) const
        {
            if constexpr (CanValidateIndexSort<T, Index>)
            {
                assert(index.sort() == T::Sort);
            }
            return data_[static_cast<size_t>(get_raw_index(index))];
        }

        size_t size() const { return size_; }

        T const * begin() const { return data_; }
        T const * end()   const { return data_ + size_; }

        T const& front() const { return *begin(); }

        Partition slice(Sequence seq)
        {
            return { data_ + static_cast<std::ptrdiff_t>(seq.start), raw_count(seq.cardinality) };
        }

        Partition drop(std::size_t n) const
        {
            return { data_ + n, size_ - n };
        }

        Partition(T const * data, size_t size)
            : data_(data)
            , size_(size)
        {}

    private:
        T const* data_;
        size_t size_;
    };
}
