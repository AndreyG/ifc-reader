module;

#include <functional>

export module reflifc:TypeId;

import :Syntax;
import :TypeSpecifier;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct TypeIdSyntax
    {
        TypeIdSyntax(ifc::File const* ifc, ifc::TypeIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        TypeSpecifierSyntax type_specifier() const
        {
        	return Syntax(ifc_, syntax_->type_specifier).as_type_specifier();
        }

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
    size_t operator()(reflifc::TypeIdSyntax object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
