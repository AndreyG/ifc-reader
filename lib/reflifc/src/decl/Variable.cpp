#include "reflifc/decl/Variable.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"
#include "reflifc/Name.h"
#include "reflifc/Type.h"

#include <ifc/Declaration.h>

namespace reflifc
{
    Name Variable::name() const
    {
        return { ifc_, var_.name };
    }

    Type Variable::type() const
    {
        return { ifc_, var_.type };
    }

    ifc::Access Variable::access() const
    {
        return var_.access;
    }

    ifc::ObjectTraits Variable::traits() const
    {
        return var_.traits;
    }

    Declaration Variable::home_scope() const
    {
        return { ifc_, var_.home_scope };
    }

    bool Variable::has_initializer() const
    {
        return !var_.initializer.is_null();
    }

    Expression Variable::initializer() const
    {
        assert(has_initializer());
        return { ifc_, var_.initializer };
    }
}
