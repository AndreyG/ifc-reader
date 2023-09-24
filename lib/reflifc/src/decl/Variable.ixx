module;

#include <functional>

export module reflifc:Variable;

import reflifc.HashCombine;

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
        friend std::hash<Variable>;

        ifc::File const* ifc_;
        ifc::VariableDeclaration const* var_;
    };
}

template<>
struct std::hash<reflifc::Variable>
{
    size_t operator()(reflifc::Variable variable) const noexcept
    {
        return reflifc::hash_combine(0, variable.ifc_, variable.var_);
    }
};
