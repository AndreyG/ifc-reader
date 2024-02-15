module;

#include <compare>

export module reflifc:FunctionType;

import :Type;
import :TupleView;

import ifc;

export namespace reflifc
{
    struct FunctionType
    {
        FunctionType(ifc::File const* ifc, ifc::FunctionType const& function)
            : ifc_(ifc)
            , function_(&function)
        {
        }

        TupleTypeView   parameters()    const { return { ifc_, function_->source }; }
        Type            return_type()   const { return { ifc_, function_->target }; }

        auto operator<=>(FunctionType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::FunctionType const* function_;
    };

    struct MethodType
    {
        MethodType(ifc::File const* ifc, ifc::MethodType const& method)
            : ifc_(ifc)
            , method_(&method)
        {
        }

        TupleTypeView   parameters()    const { return { ifc_, method_->source }; }
        Type            return_type()   const { return { ifc_, method_->target }; }
        Type            scope()         const { return { ifc_, method_->scope }; }

        ifc::FunctionTypeTraits traits() const { return method_->traits; }

        auto operator<=>(MethodType const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::MethodType const* method_;
    };
}
