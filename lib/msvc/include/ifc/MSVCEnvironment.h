#pragma once

#include "ifc/Environment.h"

namespace ifc
{
    class MSVCEnvironment final : public Environment
    {
    public:
        MSVCEnvironment(std::string const& path_to_config)
            : Environment(read_config(path_to_config))
        {}

    private:
        static Config read_config(std::string const& path);
    };
}
