#pragma once

#include <filesystem>
#include <optional>
#include <string>

import ifc.Environment;

namespace ifc
{
    Environment::Config read_msvc_config(std::string const& path_to_config, std::optional<std::filesystem::path> dir_for_relative_paths = std::nullopt);
}
