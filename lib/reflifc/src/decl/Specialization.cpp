#include "reflifc/decl/Specialization.h"

#include "reflifc/Chart.h"
#include "reflifc/Declaration.h"
#include "reflifc/TupleView.h"

#include <ifc/Declaration.h>

namespace reflifc
{
    Declaration SpecializationForm::primary_template() const
    {
        return { ifc_, form_->primary };
    }

    TupleExpressionView SpecializationForm::arguments() const
    {
        return { ifc_, form_->arguments };
    }

    Name PartialSpecialization::name() const
    {
        return { ifc_, spec_->name };
    }

    Declaration PartialSpecialization::entity() const
    {
        return { ifc_, spec_->entity.decl };
    }

    Chart PartialSpecialization::chart() const
    {
        return { ifc_, spec_->chart };
    }

    SpecializationForm PartialSpecialization::form() const
    {
        return { ifc_, ifc_->specialization_forms()[spec_->form] };
    }

    Declaration PartialSpecialization::home_scope() const
    {
        return { ifc_, spec_->home_scope };
    }

    ifc::Access PartialSpecialization::access() const
    {
        return spec_->access;
    }

    ifc::BasicSpecifiers PartialSpecialization::specifiers() const
    {
        return spec_->specifiers;
    }

    Declaration Specialization::entity() const
    {
        return { ifc_, spec_->decl };
    }

    ifc::SpecializationSort Specialization::sort() const
    {
        return spec_->sort;
    }

    SpecializationForm Specialization::form() const
    {
        return { ifc_, ifc_->specialization_forms()[spec_->form] };
    }
}
