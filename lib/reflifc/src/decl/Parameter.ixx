module;

#include <cassert>
#include <compare>
#include <functional>

export module reflifc:Parameter;

import :Chart;
import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct Parameter
    {
        Parameter(ifc::File const* ifc, ifc::ParameterDeclaration const& param)
            : ifc_(ifc)
            , param_(&param)
        {
        }

        const char* name() const { return ifc_->get_string(param_->name); }
        Type        type() const { return { ifc_, param_->type }; }

        Chart template_parameters() const
        {
        	auto forall_type = type().as_forall();
        	assert(forall_type.subject().as_fundamental().basis == ifc::TypeBasis::Typename);
        	return forall_type.chart();	        
        }

        ifc::ParameterSort sort() const { return param_->sort; }
        ifc::ParameterPosition position() const { return param_->position; }
        ifc::ParameterLevel level() const { return param_->level; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Parameter const& other) const = default;

    private:
        friend std::hash<Parameter>;

        ifc::File const* ifc_;
        ifc::ParameterDeclaration const* param_;
    };
}

template<>
struct std::hash<reflifc::Parameter>
{
    size_t operator()(reflifc::Parameter parameter) const noexcept
    {
        return reflifc::hash_combine(0, parameter.ifc_, parameter.param_);
    }
};
