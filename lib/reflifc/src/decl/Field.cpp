#include "reflifc/decl/Field.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"
#include "reflifc/Type.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

namespace reflifc
{
    const char* Field::name() const
    {
        return ifc_.get_string(field_.name);
    }

    Type Field::type() const
    {
        return { ifc_, field_.type };
    }

    ifc::Access Field::access() const
    {
        return field_.access;
    }

    ifc::ObjectTraits Field::traits() const
    {
        return field_.traits;
    }

    Declaration Field::home_scope() const
    {
        return { ifc_, field_.home_scope };
    }

    bool Field::has_initializer() const
    {
        return !field_.initializer.is_null();
    }

    Expression Field::initializer() const
    {
        assert(has_initializer());
        return { ifc_, field_.initializer };
    }
}
