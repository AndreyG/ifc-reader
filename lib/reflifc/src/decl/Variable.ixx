module;

#include <compare>

export module reflifc:Variable;

import ifc;

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Name;
    struct Type;

    export struct Variable
    {
        Variable(ifc::File const* ifc, ifc::VariableDeclaration const& var)
            : ifc_(ifc)
            , var_(&var)
        {
        }

        Name name() const;
        Type type() const;

        ifc::Access         access() const;
        ifc::ObjectTraits   traits() const;

        Declaration home_scope() const;

        bool has_initializer() const;
        Expression initializer() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Variable const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::VariableDeclaration const* var_;
    };
}
