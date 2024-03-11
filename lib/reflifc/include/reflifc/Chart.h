#pragma once

#include "reflifc/decl/Parameter.h"

#include "ViewOf.h"
#include "HashCombine.h"

#include <ifc/Chart.h>
#include <ifc/File.h>

namespace reflifc
{
    struct ChartUnilevel;

    struct Chart
    {
        Chart(ifc::File const* ifc, ifc::ChartIndex index)
            : ifc_(ifc),
              index_(index)
        {
        }

        ChartUnilevel as_unilevel() const;

        ifc::ChartSort sort() const { return index_.sort(); }

        auto operator<=>(Chart const& other) const = default;

    private:
        friend std::hash<Chart>;

        ifc::File const* ifc_;
        ifc::ChartIndex index_;
    };

    struct Expression;

    struct ChartUnilevel
    {
        ChartUnilevel(ifc::File const* ifc, ifc::ChartUnilevel const& unilevel)
            : ifc_(ifc),
              unilevel_(&unilevel)
        {
        }

        ViewOf<Parameter> auto parameters() const
        {
            return ifc_->parameters().slice(params_sequence())
                | std::views::transform([ifc = ifc_] (ifc::ParameterDeclaration const & param) { return Parameter(ifc, param); });
        }

        ifc::Sequence params_sequence() const;

        bool        has_constraint()    const;
        Expression  constraint()        const;

        auto operator<=>(ChartUnilevel const& other) const = default;

    private:
        friend std::hash<ChartUnilevel>;

        ifc::File const* ifc_;
        ifc::ChartUnilevel const* unilevel_;
    };
}

template<>
struct std::hash<reflifc::Chart>
{
    size_t operator()(reflifc::Chart object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.index_);
    }
};

template<>
struct std::hash<reflifc::ChartUnilevel>
{
    size_t operator()(reflifc::ChartUnilevel object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.unilevel_);
    }
};
