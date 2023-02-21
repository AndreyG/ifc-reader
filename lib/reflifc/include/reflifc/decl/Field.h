#pragma once

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

    private:
        ifc::File const* ifc_;
        ifc::FieldDeclaration const* field_;
    };
}
