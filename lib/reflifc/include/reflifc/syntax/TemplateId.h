#pragma once

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

    private:
        ifc::File const* ifc_;
        ifc::TemplateIdSyntax const* syntax_;
    };
}
