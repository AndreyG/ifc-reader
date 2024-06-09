module;

#include <stdexcept>
#include <cstdint>

export module ifc.Scope;

import ifc.common_types;
import ifc.Partition;

export namespace ifc
{
    using std::uint32_t;

    enum class ScopeIndex : uint32_t {};

    inline bool is_null(ScopeIndex scope)
    {
        return scope == ScopeIndex{0};
    }

    class ScopePartition : Partition<Sequence, ScopeIndex>
    {
        using Base = Partition<Sequence, ScopeIndex>;

    public:
        ScopePartition(Base base)
            : Base(base)
        {}

        Sequence operator[](ScopeIndex index) const
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
