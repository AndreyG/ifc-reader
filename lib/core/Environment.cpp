module;

#include <string>

module ifc.Environment;

import ifc.common_types;

namespace ifc
{
    std::string module_name(ModuleReference module, File const & file)
    {
        if (auto owner = module.owner; is_null(owner))
        {
            // global module
            return file.get_string(module.partition);
        }
        else
        {
            std::string name = file.get_string(owner);
            if (auto partition = module.partition; !is_null(partition))
                name.append(":").append(file.get_string(partition));
            return name;
        }
    }

    File const& Environment::get_referenced_module(ModuleReference module, File const& file)
    {
        return get_module_by_bmi_path(module_name_to_bmi_path_[module_name(module, file)]);
    }

    File const& Environment::get_module_by_bmi_path(std::filesystem::path const & key)
    {
        auto cached = cached_bmis_.find(key);
        if (cached == cached_bmis_.end())
        {
            cached = cached_bmis_.emplace_hint(cached, key, file_reader_(key));
        }
        return cached->second.ifc;
    }

    Environment::Environment(Config config, std::function<BlobHolderPtr(std::filesystem::path const &)> file_reader)
        : file_reader_(std::move(file_reader))
    {
        for (auto & [header, bmi] : config.imported_header_units)
            module_name_to_bmi_path_.emplace(std::move(header), std::move(bmi));
        for (auto & [name, bmi] : config.imported_modules)
            module_name_to_bmi_path_.emplace(std::move(name), std::move(bmi));
    }
}
