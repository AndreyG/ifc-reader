#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    Environment create_msvc_environment(std::string const& path_to_config, std::optional<std::filesystem::path> dir_for_relative_paths = std::nullopt);
}
