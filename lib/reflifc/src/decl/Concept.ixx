module;

#include <compare>

export module reflifc:Concept;

import :Chart;
import :Declaration;
import :Expression;

import ifc;

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Chart;

    export struct Concept
    {
        Concept(ifc::File const* ifc, ifc::Concept const& c)
            : ifc_(ifc)
            , c_(&c)
        {
        }

        char const* name()          const { return ifc_->get_string(c_->name); }
        Expression  definition()    const { return { ifc_, c_->constraint }; }
        Chart       chart()         const { return { ifc_, c_->chart }; }
        Declaration home_scope()    const { return { ifc_, c_->home_scope }; }

        ifc::File const* containing_file() const { return ifc_; }
        
        auto operator<=>(Concept const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Concept const* c_;
    };
}
