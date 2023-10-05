module;

#include <compare>

export module reflifc:Function;

import ifc;
import ifc.CallingConvention;
import ifc.NoexceptSpecification;

namespace reflifc
{
    struct Declaration;
    struct Name;
    struct Type;
    struct FunctionType;
    struct MethodType;
    struct TupleTypeView;

    export struct Function
    {
        Function(ifc::File const* ifc, ifc::FunctionDeclaration const& func)
            : ifc_(ifc)
            , func_(&func)
        {
        }

        Name name() const;
        FunctionType type() const;
        Declaration home_scope() const;

        ifc::Access access() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Function const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::FunctionDeclaration const* func_;
    };

    struct Method
    {
        Method(ifc::File const* ifc, ifc::MethodDeclaration const& method)
            : ifc_(ifc)
            , method_(&method)
        {
        }

        Name name() const;
        MethodType type() const;
        Declaration home_scope() const;

        ifc::Access access() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Method const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::MethodDeclaration const* method_;
    };

    struct Constructor
    {
        Constructor(ifc::File const* ifc, ifc::Constructor const& ctor)
            : ifc_(ifc)
            , ctor_(&ctor)
        {
        }

        char const* name() const;

        ifc::Access access() const;
        Declaration home_scope() const;

        TupleTypeView               parameters()    const;
        ifc::NoexceptSpecification  eh_spec()       const;
        ifc::CallingConvention      convention()    const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Constructor const& other) const = default;

    private:
        ifc::TorType const& tor_type() const;

    private:
        ifc::File const* ifc_;
        ifc::Constructor const* ctor_;
    };

    struct Destructor
    {
        Destructor(ifc::File const* ifc, ifc::Destructor const& dtor)
            : ifc_(ifc)
            , dtor_(&dtor)
        {
        }

        ifc::Access access() const;
        Declaration home_scope() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Destructor const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Destructor const* dtor_;
    };
}
