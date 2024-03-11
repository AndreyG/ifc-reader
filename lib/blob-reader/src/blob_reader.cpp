#include "ifc/blob_reader.h"

#include <boost/iostreams/device/mapped_file.hpp>

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

ifc::Environment::BlobHolderPtr ifc::read_blob(std::filesystem::path const& file)
{
    return std::make_unique<BlobHolderImpl>(file);
}
