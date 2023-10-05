module;

#include <compare>
#include <string_view>

export module reflifc.StringLiteral;

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
        ifc::File const* ifc_;
        ifc::StringLiteral literal_;
    };
}
