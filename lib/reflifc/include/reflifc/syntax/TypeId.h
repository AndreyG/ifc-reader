#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/SyntaxTreeFwd.h>

namespace reflifc
{
    struct TypeSpecifierSyntax;

    struct TypeIdSyntax
    {
        TypeIdSyntax(ifc::File const* ifc, ifc::TypeIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        TypeSpecifierSyntax type_specifier() const;

        auto operator<=>(TypeIdSyntax const& other) const = default;

    private:
        friend std::hash<TypeIdSyntax>;

        ifc::File const* ifc_;
        ifc::TypeIdSyntax const* syntax_;
    };
}

template<>
struct std::hash<reflifc::TypeIdSyntax>
{
    size_t operator()(reflifc::TypeIdSyntax const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
