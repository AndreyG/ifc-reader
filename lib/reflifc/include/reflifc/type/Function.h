#pragma once

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;
    struct TupleTypeView;

    struct FunctionType
    {
        FunctionType(ifc::File const& ifc, ifc::FunctionType const& function)
            : ifc_(ifc)
            , function_(function)
        {
        }

        TupleTypeView   parameters()    const;
        Type            return_type()   const;

    private:
        ifc::File const& ifc_;
        ifc::FunctionType const& function_;
    };

    struct MethodType
    {
        MethodType(ifc::File const& ifc, ifc::MethodType const& method)
            : ifc_(ifc)
            , method_(method)
        {
        }

        TupleTypeView   parameters()    const;
        Type            return_type()   const;
        Type            scope()         const;

        ifc::FunctionTypeTraits traits() const;

    private:
        ifc::File const& ifc_;
        ifc::MethodType const& method_;
    };
}
