module;

#include <compare>

export module reflifc:QualifiedType;

import :Type;

import ifc;

namespace reflifc
{
    export struct QualifiedType
    {
        QualifiedType(ifc::File const* ifc, ifc::QualifiedType const& qualified)
            : ifc_(ifc),
              qualified_(&qualified)
        {
        }

        Type            unqualified()   const { return { ifc_, qualified_->unqualified }; }
        ifc::Qualifiers qualifiers()    const { return qualified_->qualifiers; }

        auto operator<=>(QualifiedType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::QualifiedType const* qualified_;
    };
}
