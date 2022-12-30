#include "ifc/MSVCEnvironment.h"
#include "ifc/File.h"

#include <nlohmann/json.hpp>

#include <boost/iostreams/device/mapped_file.hpp>

#include <filesystem>
#include <fstream>

static ifc::Environment::Config read_config(std::string const& path_to_metadata, std::optional<std::filesystem::path> const& dir_for_relative_paths)
{
    std::ifstream file(path_to_metadata);
    if (!file)
        throw std::runtime_error("metadata is not found by path '" + path_to_metadata + "'");

    nlohmann::json metadata;
    file >> metadata;
    auto const & data = metadata["Data"];

    ifc::Environment::Config config;

    auto const & imported_header_units = data["ImportedHeaderUnits"];
    for (auto const & unit : imported_header_units)
    {
        std::string header = unit["Header"];
        std::filesystem::path bmi = static_cast<std::string>(unit["BMI"]);
        if (dir_for_relative_paths && bmi.is_relative())
            bmi = *dir_for_relative_paths / bmi;

        if (!is_regular_file(bmi))
        {
            std::ostringstream ss;
            ss << "cannot find BMI file " << bmi << " for header '" << header << "'";
            throw std::runtime_error(std::move(ss).str());
        }

        config.imported_header_units.push_back({ std::move(header), std::move(bmi) });
    }

    auto const & imported_modules = data["ImportedModules"];
    for (auto const & module : imported_modules)
    {
        std::string name = module["Name"];
        std::filesystem::path bmi = static_cast<std::string>(module["BMI"]);
        if (dir_for_relative_paths && bmi.is_relative())
            bmi = *dir_for_relative_paths / bmi;
        if (!is_regular_file(bmi))
        {
            std::ostringstream ss;
            ss << "cannot find BMI file " << bmi << " for module '" << name << "'";
            throw std::runtime_error(std::move(ss).str());
        }

        config.imported_modules.push_back({ std::move(name), std::move(bmi) });
    }

    return config;
}

struct BlobHolderImpl : ifc::Environment::BlobHolder
{
    boost::iostreams::mapped_file_source file_mapping;

    BlobHolderImpl(std::filesystem::path const& path)
        : file_mapping(path.string())
    {}

    ifc::File::BlobView view() const override
    {
        return as_bytes(std::span(file_mapping.data(), file_mapping.size()));
    }
};

static ifc::Environment::BlobHolderPtr file_reader(std::filesystem::path const & path)
{
    return std::make_unique<BlobHolderImpl>(path);
}

ifc::Environment ifc::create_msvc_environment(std::filesystem::path const& path_to_main_ifc, std::optional<std::filesystem::path> dir_for_relative_paths)
{
    return Environment(read_config(path_to_main_ifc.string() + ".d.json", dir_for_relative_paths), file_reader);
}
