#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    Environment::BlobHolderPtr read_blob(std::filesystem::path const & file);
}
