#include <ifc/MSVCEnvironment.h>
#include <ifc/File.h>
#include <ifc/Declaration.h>
#include <ifc/Type.h>

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

    std::string_view get_identifier(ifc::File const & file, ifc::NameIndex name)
    {
        return file.get_string(ifc::TextOffset{name.index});
    }
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

static void check_class_with_name(ifc::File const& file, ifc::DeclIndex referenced_decl, std::string_view class_name)
{
    ASSERT_EQ(referenced_decl.sort(), ifc::DeclSort::Scope);
    auto const& scope = file.scope_declarations()[referenced_decl];
    ASSERT_EQ(get_kind(scope, file), ifc::TypeBasis::Class);
    ASSERT_EQ(get_identifier(file, scope.name), class_name);
}

using namespace std::string_view_literals;

TEST(SimpleTest, IFC_dependencies)
{
    Reader reader("A.ixx.ifc");
    auto const& file = reader.get_main_ifc();
    const auto functions = file.functions();
    ASSERT_EQ(functions.size(), 1);
    auto const& function = *functions.begin();
    ASSERT_EQ(get_identifier(file, function.name), "f");
    auto const& type = file.function_types()[function.type];
    auto const& return_type = file.fundamental_types()[type.target];
    ASSERT_EQ(return_type.basis, ifc::TypeBasis::Void);
    auto const& params_type = file.tuple_types()[type.source];
    ASSERT_EQ(raw_count(params_type.cardinality), 3);
    auto params = file.type_heap().slice(params_type);
    {
        const auto referenced_decl = file.designated_types()[params[ifc::Index{0}]].decl;
        check_class_with_name(file, referenced_decl, "A");
    }
    {
        const auto referenced_decl = file.designated_types()[params[ifc::Index{1}]].decl;
        const auto decl_ref = file.decl_references()[referenced_decl];
        ASSERT_EQ(file.get_string(decl_ref.unit.owner), "A"sv);
        ASSERT_EQ(file.get_string(decl_ref.unit.partition), "B"sv);
        check_class_with_name(file.get_imported_module(decl_ref.unit), decl_ref.local_index, "B");
    }
    {
        const auto referenced_decl = file.designated_types()[params[ifc::Index{2}]].decl;
        const auto decl_ref = file.decl_references()[referenced_decl];
        ASSERT_EQ(file.get_string(decl_ref.unit.owner), "C"sv);
        check_class_with_name(file.get_imported_module(decl_ref.unit), decl_ref.local_index, "C");
    }
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
