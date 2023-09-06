#pragma once

#include "reflifc/HashCombine.h"
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

        auto operator<=>(SpecializationForm const& other) const = default;

    private:
        friend std::hash<SpecializationForm>;

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

        auto operator<=>(PartialSpecialization const& other) const = default;

    private:
        friend std::hash<PartialSpecialization>;

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

        auto operator<=>(Specialization const& other) const = default;

    private:
        friend std::hash<Specialization>;

        ifc::File const* ifc_;
        ifc::Specialization const* spec_;
    };
}

template<>
struct std::hash<reflifc::SpecializationForm>
{
    size_t operator()(reflifc::SpecializationForm specialization) const noexcept
    {
        return reflifc::hash_combine(0, specialization.ifc_, specialization.form_);
    }
};

template<>
struct std::hash<reflifc::PartialSpecialization>
{
    size_t operator()(reflifc::PartialSpecialization specialization) const noexcept
    {
        return reflifc::hash_combine(0, specialization.ifc_, specialization.spec_);
    }
};

template<>
struct std::hash<reflifc::Specialization>
{
    size_t operator()(reflifc::Specialization specialization) const noexcept
    {
        return reflifc::hash_combine(0, specialization.ifc_, specialization.spec_);
    }
};
