module;

#include <compare>

export module reflifc:Specialization;

import :Name;
import :TupleView;

import ifc;

export namespace reflifc
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

        auto operator<=>(SpecializationForm const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::SpecializationForm const* form_;
    };

    export struct PartialSpecialization
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

        auto operator<=>(PartialSpecialization const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::PartialSpecialization const* spec_;
    };

    export struct Specialization
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

        auto operator<=>(Specialization const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Specialization const* spec_;
    };
}
