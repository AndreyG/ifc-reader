#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace ifc
{
    class File;

    class Environment
    {
    public:
        virtual File const& get_module_by_bmi_path(std::filesystem::path const &) = 0;

        File const& get_module_by_name(std::string const &);

    protected:
        ~Environment() = default;

        struct Config
        {
            struct HeaderUnit
            {
                std::string header;
                std::filesystem::path bmi;
            };

            struct Module
            {
                std::string name;
                std::filesystem::path bmi;
            };

            std::vector<HeaderUnit> imported_header_units;
            std::vector<Module> imported_modules;
        };

        Environment(Config);

    private:
        std::unordered_map<std::string, std::filesystem::path> module_name_to_bmi_path_;
    };
}
