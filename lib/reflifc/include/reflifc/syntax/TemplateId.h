#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/SyntaxTreeFwd.h>

namespace reflifc
{
    struct Syntax;
    struct TupleSyntaxView;

    struct TemplateIdSyntax
    {
        TemplateIdSyntax(ifc::File const* ifc, ifc::TemplateIdSyntax const& syntax)
            : ifc_(ifc)
            , syntax_(&syntax)
        {
        }

        Syntax          name() const;
        TupleSyntaxView arguments() const;

        auto operator<=>(TemplateIdSyntax const& other) const = default;

    private:
        friend std::hash<TemplateIdSyntax>;

        ifc::File const* ifc_;
        ifc::TemplateIdSyntax const* syntax_;
    };
}

template<>
struct std::hash<reflifc::TemplateIdSyntax>
{
    size_t operator()(reflifc::TemplateIdSyntax const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.syntax_);
    }
};
