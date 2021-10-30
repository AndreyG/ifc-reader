#include "ifc/Environment.h"

#include <optional>

namespace ifc
{
    File const& Environment::get_module_by_bmi_path(std::string const & key, std::optional<std::string> const& path_to_metadata)
    {
        auto cached = cached_bmis_.find(key);
        if (cached == cached_bmis_.end())
        {
            fill_name_to_path_mapping(get_config(key, path_to_metadata));
            cached = cached_bmis_.emplace_hint(cached, key, File(key, this));
        }
        return cached->second;
    }

    File const& Environment::get_module_by_name(std::string const& name)
    {
        return get_module_by_bmi_path(module_name_to_bmi_path_[name], std::nullopt);
    }

    void Environment::fill_name_to_path_mapping(Config config)
    {
        for (auto & [header, bmi] : config.imported_header_units)
            module_name_to_bmi_path_.emplace(std::move(header), std::move(bmi));
        for (auto & [name, bmi] : config.imported_modules)
            module_name_to_bmi_path_.emplace(std::move(name), std::move(bmi));
    }
}
