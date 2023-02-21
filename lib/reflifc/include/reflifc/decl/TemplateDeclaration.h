#pragma once

#include "reflifc/Name.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Chart;
    struct Declaration;

    struct TemplateDeclaration
    {
        TemplateDeclaration(ifc::File const* ifc, ifc::TemplateDeclaration const& template_)
            : ifc_(ifc)
            , template_(template_)
        {
        }

        Name name() const;
        Declaration entity() const;
        Chart chart() const;
        Declaration home_scope() const;
        ifc::Access access() const;
        ifc::BasicSpecifiers specifiers() const;

    private:
        ifc::File const* ifc_;
        ifc::TemplateDeclaration const& template_;
    };
}
