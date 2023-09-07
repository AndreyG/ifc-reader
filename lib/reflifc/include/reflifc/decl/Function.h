#pragma once

#include "reflifc/Name.h"
#include "reflifc/HashCombine.h"

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
        friend std::hash<Function>;

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
        friend std::hash<Method>;

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
        friend std::hash<Constructor>;

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
        friend std::hash<Destructor>;

        ifc::File const* ifc_;
        ifc::Destructor const* dtor_;
    };
}

template<>
struct std::hash<reflifc::Function>
{
    size_t operator()(reflifc::Function func) const noexcept
    {
        return reflifc::hash_combine(0, func.ifc_, func.func_);
    }
};

template<>
struct std::hash<reflifc::Method>
{
    size_t operator()(reflifc::Method method) const noexcept
    {
        return reflifc::hash_combine(0, method.ifc_, method.method_);
    }
};

template<>
struct std::hash<reflifc::Constructor>
{
    size_t operator()(reflifc::Constructor constructor) const noexcept
    {
        return reflifc::hash_combine(0, constructor.ifc_, constructor.ctor_);
    }
};

template<>
struct std::hash<reflifc::Destructor>
{
    size_t operator()(reflifc::Destructor destructor) const noexcept
    {
        return reflifc::hash_combine(0, destructor.ifc_, destructor.dtor_);
    }
};
