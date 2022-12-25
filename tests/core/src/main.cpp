#include <ifc/File.h>

#include <gtest/gtest.h>

#include <boost/iostreams/device/mapped_file.hpp>

#include <filesystem>

static std::filesystem::path data_dir;

class FileWrapper
    : boost::iostreams::mapped_file_source
    , public ifc::File
{
    FileWrapper(std::filesystem::path const & path_to_ifc)
        : mapped_file_source(path_to_ifc.string())
        , File(as_bytes(std::span(data(), size())), nullptr)
    {}

public:
    static FileWrapper create(const char* filepath)
    {
        const auto path_to_ifc = data_dir / filepath;
        if (!is_regular_file(path_to_ifc))
            throw std::logic_error("'" + path_to_ifc.string() + "' is not regular file");

        return FileWrapper(path_to_ifc);
    }
};

TEST(SimpleTest, metadata)
{
    const auto file = FileWrapper::create("empty.ixx.ifc");
    const auto& header = file.header();
    ASSERT_EQ(header.major_version, ifc::Version(0));
    ASSERT_EQ(header.minor_version, ifc::Version(43));
    ASSERT_EQ(header.dialect, ifc::LanguageVersion(202002));
    ASSERT_EQ(header.arch, ifc::Architecture::X64);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    data_dir = argv[1];
    if (!is_directory(data_dir))
    {
        std::cerr << data_dir << " is not directory\n";
        return EXIT_FAILURE;
    }
    return RUN_ALL_TESTS();
}
