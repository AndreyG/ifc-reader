﻿module;

#include <optional>
#include <ranges>
#include <span>

export module reflifc:Enumeration;

import :Enumerator;

import reflifc.ViewOf;

import ifc;

namespace reflifc
{
    struct Declaration;
    struct Type;

    export struct Enumeration
    {
        Enumeration(ifc::File const* ifc, ifc::Enumeration const& enum_)
            : ifc_(ifc)
            , enum_(&enum_)
        {
        }

        char const* name() const;

        ViewOf<Enumerator> auto enumerators() const
        {
            return ifc_->enumerators().slice(enumerators_sequence())
                | std::views::transform([ifc = ifc_] (ifc::Enumerator const& enumerator) { return Enumerator(ifc, enumerator); });
        }

        Type underlying_type() const;

        Declaration home_scope() const;

        ifc::Access access() const;

        ifc::BasicSpecifiers specifiers() const;

        ifc::Sequence enumerators_sequence() const { return enum_->initializer; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Enumeration const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Enumeration const* enum_;
    };

    std::optional<Enumerator> find_enumerator_by_value(Enumeration, std::uint32_t value);
    std::optional<Enumerator> find_enumerator_by_value(Enumeration, std::span<std::byte const> value);
}
