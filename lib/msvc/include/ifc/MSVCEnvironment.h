#pragma once

#include "ifc/Environment.h"

#include <memory>

namespace ifc
{
    class MSVCEnvironment final : public Environment
    {
    public:
        MSVCEnvironment(std::filesystem::path const& path_to_main_ifc);
        ~MSVCEnvironment();

        File const& get_module_by_bmi_path(std::filesystem::path const & key) override;

    private:
        static Config read_config(std::string const& path);

        struct BMI;
        std::unordered_map<std::filesystem::path, std::unique_ptr<BMI>> cached_bmis_;
    };
}
