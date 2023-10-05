module;

#include <compare>
#include <ranges>

export module reflifc:Chart;

import :Expression;
import :Parameter;

import reflifc.ViewOf;

import ifc;

export namespace reflifc
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

        ifc::Sequence params_sequence() const { return static_cast<ifc::Sequence>(*unilevel_); }

        bool        has_constraint()    const { return !unilevel_->constraint.is_null(); }
        Expression  constraint()        const { return { ifc_, unilevel_->constraint }; }

        auto operator<=>(ChartUnilevel const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ChartUnilevel const* unilevel_;
    };

	ChartUnilevel Chart::as_unilevel() const
	{
		return { ifc_, ifc_->unilevel_charts()[index_] };
	}
}
