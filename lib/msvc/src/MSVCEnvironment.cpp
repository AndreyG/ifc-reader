#include "ifc/MSVCEnvironment.h"

#include <nlohmann/json.hpp>

#include <filesystem>
#include <fstream>

ifc::Environment::Config ifc::MSVCEnvironment::read_config(std::string const& path_to_metadata)
{
    std::ifstream file(path_to_metadata);
    if (!file)
        throw std::runtime_error("metadata is not found by path '" + path_to_metadata + "'");

    nlohmann::json metadata;
    file >> metadata;
    auto const & data = metadata["Data"];

    Config config;

    auto const & imported_header_units = data["ImportedHeaderUnits"];
    for (auto const & unit : imported_header_units)
    {
        std::string header = unit["Header"];
        std::string bmi = unit["BMI"];
        if (!is_regular_file(std::filesystem::path(bmi)))
            throw std::runtime_error("cannot find BMI file " + bmi + " for header '" + header + "'");

        config.imported_header_units.push_back({ std::move(header), std::move(bmi) });
    }

    auto const & imported_modules = data["ImportedModules"];
    for (auto const & module : imported_modules)
    {
        std::string name = module["Name"];
        std::string bmi = module["BMI"];
        if (!is_regular_file(std::filesystem::path(bmi)))
            throw std::runtime_error("cannot find BMI file " + bmi + " for module '" + name + "'");

        config.imported_modules.push_back({ std::move(name), std::move(bmi) });
    }

    return config;
}
