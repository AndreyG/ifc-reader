#pragma once

#include "reflifc/Name.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Chart;
    struct Declaration;

    struct SpecializationForm
    {
        SpecializationForm(ifc::File const* ifc, ifc::SpecializationForm const& form)
            : ifc_(ifc)
            , form_(&form)
        {}

        Declaration primary_template()  const;
        TupleExpressionView arguments() const;

        ifc::File const* containing_file() const { return ifc_; }

    private:
        ifc::File const* ifc_;
        ifc::SpecializationForm const* form_;
    };

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
        SpecializationForm form() const;
        Declaration home_scope() const;
        ifc::Access access() const;
        ifc::BasicSpecifiers specifiers() const;

        ifc::File const* containing_file() const { return ifc_; }

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
        SpecializationForm form() const;

        ifc::File const* containing_file() const { return ifc_; }

    private:
        ifc::File const* ifc_;
        ifc::Specialization const* spec_;
    };
}
