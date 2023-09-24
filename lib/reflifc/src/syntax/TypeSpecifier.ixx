module;

#include <functional>

export module reflifc:TypeSpecifier;

import :Syntax;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct TypeSpecifierSyntax
    {
        TypeSpecifierSyntax(ifc::File const* ifc, ifc::TypeSpecifierSeq const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        Syntax typename_() const { return { ifc_, syntax_->typename_ }; }

        auto operator<=>(TypeSpecifierSyntax const& other) const = default;

    private:
        friend std::hash<TypeSpecifierSyntax>;

        ifc::File const* ifc_;
        ifc::TypeSpecifierSeq const* syntax_;
    };
}

template<>
struct std::hash<reflifc::TypeSpecifierSyntax>
{
    size_t operator()(reflifc::TypeSpecifierSyntax object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
