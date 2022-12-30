#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    Environment create_msvc_environment(std::filesystem::path const& path_to_main_ifc, std::optional<std::filesystem::path> dir_for_relative_paths = std::nullopt);
}
