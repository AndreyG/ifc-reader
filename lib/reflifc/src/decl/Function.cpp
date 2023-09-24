module reflifc;

namespace reflifc
{
    Name Function::name() const
    {
        return { ifc_, func_->name };
    }

    FunctionType Function::type() const
    {
        return Type(ifc_, func_->type).as_function();
    }

    Declaration Function::home_scope() const
    {
        return { ifc_, func_->home_scope };
    }

    ifc::Access Function::access() const
    {
        return func_->access;
    }

    Name Method::name() const
    {
        return { ifc_, method_->name };
    }

    MethodType Method::type() const
    {
        return Type(ifc_, method_->type).as_method();
    }

    Declaration Method::home_scope() const
    {
        return { ifc_, method_->home_scope };
    }

    ifc::Access Method::access() const
    {
        return method_->access;
    }

    char const* Constructor::name() const
    {
        return ifc_->get_string(ctor_->name);
    }

    ifc::Access Constructor::access() const
    {
        return ctor_->access;
    }

    Declaration Constructor::home_scope() const
    {
        return { ifc_, ctor_->home_scope };
    }

    TupleTypeView Constructor::parameters() const
    {
        return { ifc_, tor_type().source };
    }

    ifc::TorType const& Constructor::tor_type() const
    {
        return ifc_->tor_types()[ctor_->type];
    }

    ifc::Access Destructor::access() const
    {
        return dtor_->access;
    }

    Declaration Destructor::home_scope() const
    {
        return { ifc_, dtor_->home_scope };
    }

    ifc::NoexceptSpecification Constructor::eh_spec() const
    {
        return tor_type().eh_spec;
    }

    ifc::CallingConvention Constructor::convention() const
    {
        return tor_type().convention;
    }
}
