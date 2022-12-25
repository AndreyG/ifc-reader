#include "ifc/Environment.h"

namespace ifc
{
    File const& Environment::get_module_by_name(std::string const& name)
    {
        return get_module_by_bmi_path(module_name_to_bmi_path_[name]);
    }

    Environment::Environment(Config config)
    {
        for (auto & [header, bmi] : config.imported_header_units)
            module_name_to_bmi_path_.emplace(std::move(header), std::move(bmi));
        for (auto & [name, bmi] : config.imported_modules)
            module_name_to_bmi_path_.emplace(std::move(name), std::move(bmi));
    }
}
