#include "reflifc/StringLiteral.h"

#include <ifc/File.h>

namespace reflifc
{
    std::string_view StringLiteral::value() const
    {
        return { ifc_->get_string(literal_.start), raw_count(literal_.length) - 1 };
    }
}
