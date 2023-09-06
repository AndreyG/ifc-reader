#pragma once

#include "HashCombine.h"

#include <ifc/SyntaxTreeFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Expression;
    struct TemplateIdSyntax;
    struct TypeIdSyntax;
    struct TypeSpecifierSyntax;
    struct TypeTraitIntrinsicSyntax;

    struct Syntax
    {
        Syntax(ifc::File const* ifc, ifc::SyntaxIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        ifc::SyntaxSort sort() const { return index_.sort(); }

        TemplateIdSyntax            as_template_id()            const;
        Expression                  as_expression()             const;
        TypeIdSyntax                as_type_id()                const;
        TypeSpecifierSyntax         as_type_specifier()         const;
        Syntax                      as_type_template_argument() const;
        TypeTraitIntrinsicSyntax    as_type_trait_intrinsic()   const;
        Expression                  requires_clause_condition() const;

        auto operator<=>(Syntax const& other) const = default;

    private:
        friend std::hash<Syntax>;

        ifc::File const* ifc_;
        ifc::SyntaxIndex index_;
    };
}

template<>
struct std::hash<reflifc::Syntax>
{
    size_t operator()(reflifc::Syntax object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.index_);
    }
};
