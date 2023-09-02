#pragma once

#include "reflifc/Expression.h"
#include "reflifc/Literal.h"
#include "reflifc/HashCombine.h"

#include <ifc/DeclarationFwd.h>

namespace reflifc
{
    struct Enumerator
    {
        Enumerator(ifc::File const* ifc, ifc::Enumerator const& enumerator)
            : ifc_(ifc)
            , enumerator_(&enumerator)
        {
        }

        const char* name() const;

        Expression value() const;

        auto operator<=>(Enumerator const& other) const = default;

    private:
        friend std::hash<Enumerator>;

        ifc::File const* ifc_;
        ifc::Enumerator const* enumerator_;
    };

    inline auto int_value(Enumerator enumerator)
    {
        return enumerator.value().as_literal().int_value();
    }
}

template<>
struct std::hash<reflifc::Enumerator>
{
    size_t operator()(reflifc::Enumerator const& enumerator) const noexcept
    {
        return reflifc::hash_combine(0, enumerator.ifc_, enumerator.enumerator_);
    }
};
