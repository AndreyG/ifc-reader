#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    Environment::Config read_msvc_config(std::string const& path_to_config, std::optional<std::filesystem::path> dir_for_relative_paths = std::nullopt);
}
