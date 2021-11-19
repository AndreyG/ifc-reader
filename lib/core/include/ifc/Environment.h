#pragma once

#include "File.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace ifc
{
    class Environment
    {
    public:
        File const & get_module_by_bmi_path (std::string const &);
        File const & get_module_by_name     (std::string const &);

    protected:
        ~Environment();

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

        Environment();
        Environment(Config);

    private:
        std::unordered_map<std::string, File> cached_bmis_;
        std::unordered_map<std::string, std::string> module_name_to_bmi_path_;
    };
}
