#pragma once

#include "ifc/Environment.h"

#include <memory>

namespace ifc
{
    class MSVCEnvironment final : public Environment
    {
    public:
        MSVCEnvironment(std::string const& path_to_config);
        ~MSVCEnvironment();

        File const& get_module_by_bmi_path(std::string const & key) override;

    private:
        static Config read_config(std::string const& path);

        struct BMI;
        std::unordered_map<std::string, std::unique_ptr<BMI>> cached_bmis_;
    };
}
