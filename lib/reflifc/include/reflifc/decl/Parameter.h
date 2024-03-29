﻿#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/Declaration.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Type;
    struct Chart;

    struct Parameter
    {
        Parameter(ifc::File const* ifc, ifc::ParameterDeclaration const& param)
            : ifc_(ifc)
            , param_(&param)
        {
        }

        const char* name() const;
        Type        type() const;

        Chart template_parameters() const;

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
