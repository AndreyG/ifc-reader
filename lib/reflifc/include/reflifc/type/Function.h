#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/TypeFwd.h>

namespace reflifc
{
    struct Type;
    struct TupleTypeView;

    struct FunctionType
    {
        FunctionType(ifc::File const* ifc, ifc::FunctionType const& function)
            : ifc_(ifc)
            , function_(&function)
        {
        }

        TupleTypeView   parameters()    const;
        Type            return_type()   const;

        auto operator<=>(FunctionType const& other) const = default;

    private:
        friend std::hash<FunctionType>;

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

        TupleTypeView   parameters()    const;
        Type            return_type()   const;
        Type            scope()         const;

        ifc::FunctionTypeTraits traits() const;

        auto operator<=>(MethodType const& other) const = default;

    private:
        friend std::hash<MethodType>;

        ifc::File const* ifc_;
        ifc::MethodType const* method_;
    };
}

template<>
struct std::hash<reflifc::FunctionType>
{
    size_t operator()(reflifc::FunctionType const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.function_);
    }
};

template<>
struct std::hash<reflifc::MethodType>
{
    size_t operator()(reflifc::MethodType const& object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.method_);
    }
};
