module;

#include <compare>

export module reflifc:Parameter;

import :Type;

import ifc;

namespace reflifc
{
    struct Chart;

    export struct Parameter
    {
        Parameter(ifc::File const* ifc, ifc::ParameterDeclaration const& param)
            : ifc_(ifc)
            , param_(&param)
        {
        }

        const char* name() const { return ifc_->get_string(param_->name); }
        Type        type() const { return { ifc_, param_->type }; }

        Chart template_parameters() const;

        ifc::ParameterSort sort() const { return param_->sort; }
        ifc::ParameterPosition position() const { return param_->position; }
        ifc::ParameterLevel level() const { return param_->level; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Parameter const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ParameterDeclaration const* param_;
    };
}
