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
