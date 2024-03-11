#include "reflifc/type/Function.h"

#include "reflifc/TupleView.h"
#include "reflifc/Type.h"

#include <ifc/Type.h>

namespace reflifc
{
    TupleTypeView FunctionType::parameters() const
    {
        return { ifc_, function_->source };
    }

    Type FunctionType::return_type() const
    {
        return { ifc_, function_->target };
    }

    TupleTypeView MethodType::parameters() const
    {
        return { ifc_, method_->source };
    }

    Type MethodType::return_type() const
    {
        return { ifc_, method_->target };
    }

    Type MethodType::scope() const
    {
        return { ifc_, method_->scope };
    }

    ifc::FunctionTypeTraits MethodType::traits() const
    {
        return method_->traits;
    }
}
