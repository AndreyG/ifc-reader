#include "reflifc/decl/TemplateDeclaration.h"

#include "reflifc/Chart.h"
#include "reflifc/Declaration.h"

#include <ifc/Declaration.h>

namespace reflifc
{
    Name TemplateDeclaration::name() const
    {
        return { ifc_, template_.name };
    }

    Declaration TemplateDeclaration::entity() const
    {
        return { ifc_, template_.entity.decl };
    }

    Chart TemplateDeclaration::chart() const
    {
        return { ifc_, template_.chart };
    }

    Declaration TemplateDeclaration::home_scope() const
    {
        return { ifc_, template_.home_scope };
    }

    ifc::Access TemplateDeclaration::access() const
    {
        return template_.access;
    }

    ifc::BasicSpecifiers TemplateDeclaration::specifiers() const
    {
        return template_.specifiers;
    }
}
