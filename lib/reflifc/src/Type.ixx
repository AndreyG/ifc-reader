module;

#include <compare>

export module reflifc:Type;

import ifc;

namespace reflifc
{
    struct ArrayType;
    struct BaseType;
    struct Declaration;
    struct LvalueReference;
    struct RvalueReference;
    struct PointerType;
    struct FunctionType;
    struct MethodType;
    struct QualifiedType;
    struct ExpansionType;
    struct ForallType;
    struct PlaceholderType;

    struct Declaration;
    struct Expression;
    struct PathExpression;

    export struct Type
    {
        Type(ifc::File const* ifc, ifc::TypeIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        explicit operator bool() const
        {
            return !index_.is_null();
        }

        bool                    is_fundamental() const;
        ifc::FundamentalType    as_fundamental() const;

        bool            is_array() const;
        ArrayType       as_array() const;

        bool            is_designated() const;
        Declaration     designation()   const;

        bool            is_syntactic() const;
        Expression      as_syntactic() const;

        bool            is_base() const;
        BaseType        as_base() const;

        bool            is_lvalue_reference() const;
        LvalueReference as_lvalue_reference() const;

        bool            is_rvalue_reference() const;
        RvalueReference as_rvalue_reference() const;

        bool            is_pointer() const;
        PointerType     as_pointer() const;

        bool            is_function() const;
        FunctionType    as_function() const;

        bool            is_method() const;
        MethodType      as_method() const;

        bool            is_qualified() const;
        QualifiedType   as_qualified() const;

        bool            is_expansion() const;
        ExpansionType   as_expansion() const;

        bool            is_forall() const;
        ForallType      as_forall() const;

        bool            is_decltype() const;
        Expression      decltype_argument() const;

        bool            is_placeholder() const;
        PlaceholderType as_placeholder() const;

        bool            is_typename() const;
        PathExpression  typename_path() const;

        ifc::TypeSort sort() const { return index_.sort(); }

        auto operator<=>(Type const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::TypeIndex index_;
    };
}
