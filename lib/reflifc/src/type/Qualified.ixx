module;

#include <functional>

export module reflifc:QualifiedType;

import :Type;

import reflifc.HashCombine;

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
        friend std::hash<QualifiedType>;

        ifc::File const* ifc_;
        ifc::QualifiedType const* qualified_;
    };
}

template<>
struct std::hash<reflifc::QualifiedType>
{
    size_t operator()(reflifc::QualifiedType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.qualified_);
    }
};
