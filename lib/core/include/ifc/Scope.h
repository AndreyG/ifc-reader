#pragma once

#include "common_types.h"

#include <string_view>

namespace ifc
{
    enum class ScopeIndex : uint32_t {};

    struct ScopeDescriptor : Sequence
    {
        static constexpr std::string_view PartitionName = "scope.desc";
    };
}
