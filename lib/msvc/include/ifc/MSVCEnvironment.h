#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    class MSVCEnvironment final : public Environment
    {
    protected:
        Config get_config(std::string const& path_to_bmi, std::optional<std::string> const&) const override;
    };
}
