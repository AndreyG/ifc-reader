#pragma once

#include <filesystem>

import ifc.Environment;

namespace ifc
{
    Environment::BlobHolderPtr read_blob(std::filesystem::path const & file);
}
