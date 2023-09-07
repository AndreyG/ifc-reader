#pragma once

#include "Enumerator.h"

#include "reflifc/ViewOf.h"
#include "reflifc/HashCombine.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

#include <optional>

namespace reflifc
{
    struct Declaration;
    struct Type;

    struct Enumeration
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
        friend std::hash<Enumeration>;

        ifc::File const* ifc_;
        ifc::Enumeration const* enum_;
    };

    std::optional<Enumerator> find_enumerator_by_value(Enumeration, std::uint32_t value);
    std::optional<Enumerator> find_enumerator_by_value(Enumeration, std::span<std::byte const> value);
}

template<>
struct std::hash<reflifc::Enumeration>
{
    size_t operator()(reflifc::Enumeration enumeration) const noexcept
    {
        return reflifc::hash_combine(0, enumeration.ifc_, enumeration.enum_);
    }
};
