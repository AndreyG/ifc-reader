module;

#include <functional>
#include <string_view>

export module reflifc.StringLiteral;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct StringLiteral
    {
        StringLiteral(ifc::File const* file, ifc::StringLiteral literal)
            : ifc_(file)
            , literal_(literal)
        {
        }

        std::string_view value() const { return { ifc_->get_string(literal_.start), raw_count(literal_.length) - 1 }; }

        auto operator<=>(StringLiteral const& other) const = default;

    private:
        friend std::hash<StringLiteral>;

        ifc::File const* ifc_;
        ifc::StringLiteral literal_;
    };
}

template<>
struct std::hash<reflifc::StringLiteral>
{
    size_t operator()(reflifc::StringLiteral object) const noexcept
    {
        return reflifc::hash_combine(0, object.ifc_, object.literal_.start, object.literal_.length, object.literal_.suffix);
    }
};
