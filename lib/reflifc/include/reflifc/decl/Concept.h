#pragma once

#include "reflifc/HashCombine.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Declaration;
    struct Expression;
    struct Chart;

    struct Concept
    {
        Concept(ifc::File const* ifc, ifc::Concept const& c)
            : ifc_(ifc)
            , c_(&c)
        {
        }

        char const* name()          const;
        Expression  definition()    const;
        Chart       chart()         const;
        Declaration home_scope()    const;

        ifc::File const* containing_file() const { return ifc_; }
        
        auto operator<=>(Concept other) const = default;

    private:
        friend std::hash<Concept>;

        ifc::File const* ifc_;
        ifc::Concept const* c_;
    };
}

template<>
struct std::hash<reflifc::Concept>
{
    size_t operator()(reflifc::Concept concept_) const noexcept
    {
        return reflifc::hash_combine(0, concept_.ifc_, concept_.c_);
    }
};
