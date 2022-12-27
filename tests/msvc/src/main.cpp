#include <ifc/MSVCEnvironment.h>
#include <ifc/File.h>

#include <gtest/gtest.h>

#include <filesystem>

static std::filesystem::path data_dir;

namespace
{
    class Reader
    {
        struct PathToIFC
        {
            std::filesystem::path full_path;

            explicit PathToIFC(const char* filename)
                : full_path(data_dir / filename)
            {
                if (!is_regular_file(full_path))
                {
                    std::ostringstream ss;
                    ss << full_path << " is not regular file";
                    throw std::logic_error(std::move(ss).str());
                }
            }
        } path_to_ifc;

        ifc::MSVCEnvironment environment;

    public:
        explicit Reader(const char* filename)
            : path_to_ifc(filename)
            , environment(path_to_ifc.full_path, data_dir)
        {}

        ifc::File const& get_main_ifc()
        {
            return environment.get_module_by_bmi_path(path_to_ifc.full_path);
        }
    };
}

TEST(SimpleTest, metadata)
{
    Reader reader("empty.ixx.ifc");
    const auto& file = reader.get_main_ifc();
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
