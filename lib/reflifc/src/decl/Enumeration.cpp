#include "reflifc/decl/Enumeration.h"

#include "reflifc/Declaration.h"
#include "reflifc/Type.h"

#include <cstring>

namespace reflifc
{
    char const* Enumeration::name() const
    {
        return ifc_.get_string(enum_.name);
    }

    Type Enumeration::underlying_type() const
    {
        return { ifc_, enum_.base };
    }

    Declaration Enumeration::home_scope() const
    {
        return { ifc_, enum_.home_scope };
    }

    ifc::Access Enumeration::access() const
    {
        return enum_.access;
    }

    ifc::BasicSpecifiers Enumeration::specifiers() const
    {
        return enum_.specifiers;
    }

    std::optional<Enumerator> find_enumerator_by_value(Enumeration enumeration, std::uint32_t value)
    {
        for (Enumerator enumerator : enumeration.enumerators())
            if (int_value(enumerator) == value)
                return enumerator;

        return std::nullopt;
    }

    std::optional<Enumerator> find_enumerator_by_value(Enumeration enumeration, std::span<std::byte const> value)
    {
        for (Enumerator enumerator : enumeration.enumerators())
        {
            auto enumerator_value = int_value(enumerator);
            if (std::memcmp(&enumerator_value, value.data(), value.size()) == 0)
                return enumerator;
        }

        return std::nullopt;
    }
}
