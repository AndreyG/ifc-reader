module;

#include <functional>

export module reflifc:ArrayType;

import :Expression;
import :Type;

import reflifc.Literal;
import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct ArrayType
    {
        ArrayType(ifc::File const* ifc, ifc::ArrayType const& array)
            : ifc_(ifc)
            , array_(&array)
        {
        }

        Type        element() const { return { ifc_, array_->element }; }
        Expression  extent()  const { return { ifc_, array_->extent }; }

        auto operator<=>(ArrayType const& other) const = default;

    private:
        friend std::hash<ArrayType>;

        ifc::File const* ifc_;
        ifc::ArrayType const* array_;
    };

    export std::uint32_t extent_value(ArrayType array)
    {
    	return array.extent().as_literal().int_value();
    }
}

template<>
struct std::hash<reflifc::ArrayType>
{
    size_t operator()(reflifc::ArrayType object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.array_);
    }
};
