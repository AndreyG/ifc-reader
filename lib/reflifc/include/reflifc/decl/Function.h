#pragma once

#include "reflifc/Name.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>
#include <ifc/CallingConvention.h>
#include <ifc/NoexceptSpecification.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Type;
    struct FunctionType;
    struct MethodType;
    struct TupleTypeView;

    struct Function
    {
        Function(ifc::File const& ifc, ifc::FunctionDeclaration const& func)
            : ifc_(ifc)
            , func_(func)
        {
        }

        Name name() const;
        FunctionType type() const;
        Declaration home_scope() const;

        ifc::Access access() const;

    private:
        ifc::File const & ifc_;
        ifc::FunctionDeclaration const& func_;
    };

    struct Method
    {
        Method(ifc::File const& ifc, ifc::MethodDeclaration const& method)
            : ifc_(ifc)
            , method_(method)
        {
        }

        Name name() const;
        MethodType type() const;
        Declaration home_scope() const;

        ifc::Access access() const;

    private:
        ifc::File const & ifc_;
        ifc::MethodDeclaration const& method_;
    };

    struct Constructor
    {
        Constructor(ifc::File const& ifc, ifc::Constructor const& ctor)
            : ifc_(ifc)
            , ctor_(ctor)
        {
        }

        char const* name() const;

        ifc::Access access() const;
        Declaration home_scope() const;

        TupleTypeView               parameters()    const;
        ifc::NoexceptSpecification  eh_spec()       const;
        ifc::CallingConvention      convention()    const;

    private:
        ifc::TorType const& tor_type() const;

    private:
        ifc::File const & ifc_;
        ifc::Constructor const& ctor_;
    };

    struct Destructor
    {
        Destructor(ifc::File const& ifc, ifc::Destructor const& dtor)
            : ifc_(ifc)
            , dtor_(dtor)
        {
        }

        ifc::Access access() const;
        Declaration home_scope() const;

    private:
        ifc::File const & ifc_;
        ifc::Destructor const& dtor_;
    };
}
