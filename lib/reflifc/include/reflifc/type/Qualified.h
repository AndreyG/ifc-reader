#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;

    struct QualifiedType
    {
        QualifiedType(ifc::File const* ifc, ifc::QualifiedType const& qualified)
            : ifc_(ifc),
              qualified_(qualified)
        {
        }

        Type            unqualified()   const;
        ifc::Qualifiers qualifiers()    const;

        auto operator<=>(QualifiedType const& other) const = default;

    private:
        friend std::hash<QualifiedType>;

        ifc::File const* ifc_;
        ifc::QualifiedType const& qualified_;
    };
}

template<>
struct std::hash<reflifc::QualifiedType>
{
    size_t operator()(reflifc::QualifiedType const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.qualified_);
    }
};
