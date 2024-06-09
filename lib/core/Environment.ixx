module;

#include <filesystem>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

export module ifc.Environment;

import ifc;
import ifc.Module;

namespace ifc
{
    export class Environment
    {
    public:
        class BlobHolder
        {
        public:
            virtual File::BlobView view() const = 0;
            virtual ~BlobHolder() = default;
        };

        using BlobHolderPtr = std::unique_ptr<BlobHolder>;

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

        File const& get_module_by_bmi_path(std::filesystem::path const &);
        File const& get_referenced_module(ModuleReference, File const&);

        Environment(Config, std::function<BlobHolderPtr(std::filesystem::path const &)> file_reader);

    private:
        struct CachedBMI
        {
        private:
            BlobHolderPtr blob_;

        public:
            File ifc;

            CachedBMI(BlobHolderPtr blob)
                : blob_(std::move(blob))
                , ifc(blob_->view())
            {}
        };

    private:
        std::function<BlobHolderPtr(std::filesystem::path const &)> file_reader_;
        std::unordered_map<std::string, std::filesystem::path> module_name_to_bmi_path_;

        // See https://cplusplus.github.io/LWG/issue3657
        struct PathHasher
        {
            size_t operator() (std::filesystem::path const & path) const noexcept
            {
                return hash_value(path);
            }
        };

        std::unordered_map<std::filesystem::path, CachedBMI, PathHasher> cached_bmis_;
    };
}

module :private;

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
