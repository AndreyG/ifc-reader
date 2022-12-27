#pragma once

#include "ifc/Environment.h"

#include <memory>
#include <optional>

namespace ifc
{
    class MSVCEnvironment final : public Environment
    {
    public:
        MSVCEnvironment(std::filesystem::path const& path_to_main_ifc,
                        std::optional<std::filesystem::path> dir_for_relative_paths = std::nullopt);
        ~MSVCEnvironment();

        File const& get_module_by_bmi_path(std::filesystem::path const & key) override;

    private:
        static Config read_config(std::string const& path, std::optional<std::filesystem::path> const& dir_for_relative_paths);

        struct BMI;

        // See https://cplusplus.github.io/LWG/issue3657
        struct PathHasher
        {
            size_t operator() (std::filesystem::path const & path) const noexcept
            {
                return hash_value(path);
            }
        };

        std::unordered_map<std::filesystem::path, std::unique_ptr<BMI>, PathHasher> cached_bmis_;
    };
}
