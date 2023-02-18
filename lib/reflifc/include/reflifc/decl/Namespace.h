#pragma once

#include "Scope.h"

#include "reflifc/Name.h"

#include <ifc/File.h>
#include <ifc/Declaration.h>

namespace reflifc
{
    struct Namespace
    {
        Namespace(ifc::File const& ifc, ifc::ScopeDeclaration const& scope)
            : ifc_(ifc)
            , scope_(scope)
        {
        }

        Name  name()  const { return { ifc_, scope_.name }; }
        Scope scope() const { return { ifc_, scope_.initializer }; }

        bool is_inline() const { return ifc::is_inline(scope_); }

    private:
        ifc::File const & ifc_;
        ifc::ScopeDeclaration const& scope_;
    };
}
