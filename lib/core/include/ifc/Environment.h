#pragma once

#include "File.h"

#include <unordered_map>
#include <vector>
#include <optional>

namespace ifc
{
    class Environment
    {
    public:
        File const & get_module_by_bmi_path (std::string const &, std::optional<std::string> const&);
        File const & get_module_by_name     (std::string const &);

    protected:
        ~Environment() = default;

        struct Config
        {
            struct HeaderUnit
            {
                std::string header;
                std::string bmi;
            };

            struct Module
            {
                std::string name;
                std::string bmi;
            };

            std::vector<HeaderUnit> imported_header_units;
            std::vector<Module> imported_modules;
        };

        virtual Config get_config(std::string const & path_to_bmi, std::optional<std::string> const&) const = 0;

    private:
        void fill_name_to_path_mapping(Config);

    private:
        std::unordered_map<std::string, File> cached_bmis_;
        std::unordered_map<std::string, std::string> module_name_to_bmi_path_;
    };
}
