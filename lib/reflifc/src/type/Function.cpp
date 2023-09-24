module reflifc;

namespace reflifc
{

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
