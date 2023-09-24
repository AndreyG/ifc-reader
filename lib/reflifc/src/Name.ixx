module;

#include <functional>
#include <string_view>

export module reflifc:Name;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct SpecializationName;
    struct TupleExpressionView;

    export struct Name
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

        bool        is_identifier() const;
        char const* as_identifier() const;

        bool        is_operator() const;
        char const* operator_name() const;

        ifc::Operator get_operator() const;

        bool        is_literal() const;
        char const* as_literal() const;

        bool                is_specialization() const;
        SpecializationName  as_specialization() const;

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

    export inline bool is_identifier(Name name, std::string_view s)
    {
        return name.is_identifier() && name.as_identifier() == s;
    }

    export template<typename Declaration>
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
