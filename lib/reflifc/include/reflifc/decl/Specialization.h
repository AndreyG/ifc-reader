#pragma once

#include "reflifc/Name.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Chart;
    struct Declaration;

    struct PartialSpecialization
    {
        PartialSpecialization(ifc::File const* ifc, ifc::PartialSpecialization const& spec)
            : ifc_(ifc)
            , spec_(&spec)
        {
        }

        Name name() const;
        Declaration entity() const;
        Chart chart() const;
        Declaration home_scope() const;
        ifc::Access access() const;
        ifc::BasicSpecifiers specifiers() const;

    private:
        ifc::File const* ifc_;
        ifc::PartialSpecialization const* spec_;
    };

    struct Specialization
    {
        Specialization(ifc::File const* ifc, ifc::Specialization const& spec)
            : ifc_(ifc)
            , spec_(&spec)
        {
        }

        Declaration entity() const;
        ifc::SpecializationSort sort() const;

    private:
        ifc::File const* ifc_;
        ifc::Specialization const* spec_;
    };
}
