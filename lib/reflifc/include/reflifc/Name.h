#pragma once

#include "HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/Name.h>

#include <string_view>

namespace reflifc
{
    struct SpecializationName;
    struct TupleExpressionView;
    struct Declaration;
    struct Type;

    struct Name
    {
        Name(ifc::File const* ifc, ifc::NameIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        explicit operator bool() const
        {
            return !index_.is_null();
        }

        bool                is_identifier() const;
        char const*         as_identifier() const;

        bool                is_operator() const;
        char const*         operator_name() const;
        ifc::Operator       get_operator() const;

        bool                is_literal() const;
        char const*         as_literal() const;

        bool                is_conversion() const;
        char const*         as_conversion_name() const;
        Type			    get_conversion_target_type() const;

        bool                is_template() const;
        Name				as_template() const;

        bool                is_specialization() const;
        SpecializationName  as_specialization() const;

        bool                is_soure_file() const;
        char const*         as_source_file() const;
        char const*         get_source_file_header_guard() const;

        bool                is_deduction_guide() const;
        Declaration			as_deduction_guide() const;

        ifc::NameSort sort() const { return index_.sort(); }

        auto operator<=>(Name const& other) const = default;

    private:
        friend std::hash<Name>;

        ifc::File const* ifc_;
        ifc::NameIndex index_;
    };

    struct SpecializationName
    {
        SpecializationName(ifc::File const* ifc, ifc::SpecializationName const& specialization)
            : ifc_(ifc)
            , specialization_(&specialization)
        {
        }

        Name                primary()               const;
        TupleExpressionView template_arguments()    const;

        auto operator<=>(SpecializationName const& other) const = default;

    private:
        friend std::hash<SpecializationName>;

        ifc::File const* ifc_;
        ifc::SpecializationName const* specialization_;
    };

    inline bool is_identifier(Name name, std::string_view s)
    {
        return name.is_identifier() && name.as_identifier() == s;
    }

    template<typename Declaration>
    bool has_name(Declaration declaration, std::string_view s)
    {
        return is_identifier(declaration.name(), s);
    }
}

template<>
struct std::hash<reflifc::Name>
{
    size_t operator()(reflifc::Name object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.index_);
    }
};

template<>
struct std::hash<reflifc::SpecializationName>
{
    size_t operator()(reflifc::SpecializationName object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.specialization_);
    }
};
