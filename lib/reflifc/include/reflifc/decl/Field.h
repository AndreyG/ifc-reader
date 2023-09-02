#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Type;

    struct Field
    {
        Field(ifc::File const* ifc, ifc::FieldDeclaration const& field)
            : ifc_(ifc)
            , field_(&field)
        {
        }

        const char* name() const;
        Type        type() const;

        ifc::Access         access() const;
        ifc::ObjectTraits   traits() const;

        Declaration home_scope() const;

        bool has_initializer() const;
        Expression initializer() const;

        auto operator<=>(Field const& other) const = default;

    private:
        friend std::hash<Field>;

        ifc::File const* ifc_;
        ifc::FieldDeclaration const* field_;
    };
}

template<>
struct std::hash<reflifc::Field>
{
    size_t operator()(reflifc::Field const& field) const noexcept
    {
        return reflifc::hash_combine(0, field.ifc_, field.field_);
    }
};
