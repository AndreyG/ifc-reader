#include <ifc/MSVCEnvironment.h>
#include <ifc/File.h>

#include <gtest/gtest.h>

#include <filesystem>

static std::filesystem::path data_dir;

TEST(SimpleTest, metadata)
{
    const auto path_to_ifc = data_dir / "empty.ixx.ifc";
    ASSERT_TRUE(is_regular_file(path_to_ifc));
    ifc::MSVCEnvironment env(path_to_ifc);
    const auto& file = env.get_module_by_bmi_path(path_to_ifc);
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
