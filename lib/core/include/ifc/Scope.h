#pragma once

#include "Partition.h"

#include <stdexcept>
#include <string_view>

namespace ifc
{
    enum class ScopeIndex : uint32_t {};

    inline bool is_null(ScopeIndex scope)
    {
        return scope == ScopeIndex{0};
    }

    struct ScopeDescriptor : Sequence
    {
        static constexpr std::string_view PartitionName = "scope.desc";
    };

    class ScopePartition : Partition<ScopeDescriptor, ScopeIndex>
    {
        using Base = Partition<ScopeDescriptor, ScopeIndex>;

    public:
        ScopePartition(Base base)
            : Base(base)
        {}

        ScopeDescriptor operator[](ScopeIndex index) const
        {
            if (is_null(index))
                throw std::out_of_range("scope indices start from 1");

            return Base::operator[](ScopeIndex{static_cast<uint32_t>(index) - 1});
        }

        using Base::size;
        using Base::begin;
        using Base::end;
    };
}
