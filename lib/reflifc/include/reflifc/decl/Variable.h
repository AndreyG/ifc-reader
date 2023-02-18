#pragma once

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Name;
    struct Type;

    struct Variable
    {
        Variable(ifc::File const& ifc, ifc::VariableDeclaration const& var)
            : ifc_(ifc)
            , var_(var)
        {
        }

        Name name() const;
        Type type() const;

        ifc::Access         access() const;
        ifc::ObjectTraits   traits() const;

        Declaration home_scope() const;

        bool has_initializer() const;
        Expression initializer() const;

    private:
        ifc::File const & ifc_;
        ifc::VariableDeclaration const& var_;
    };
}
