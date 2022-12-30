#include <ifc/Attribute.h>
#include <ifc/Declaration.h>
#include <ifc/File.h>
#include <ifc/Type.h>

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
        , File(as_bytes(std::span(data(), size())))
    {}

public:
    static FileWrapper create(const char* filepath)
    {
        const auto path_to_ifc = data_dir / filepath;
        if (!is_regular_file(path_to_ifc))
            throw std::logic_error("'" + path_to_ifc.string() + "' is not regular file");

        return FileWrapper(path_to_ifc);
    }

    std::string_view get_identifier(ifc::NameIndex name) const
    {
        return get_string(ifc::TextOffset{name.index});
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

namespace
{
    void check_identifier_attribute(ifc::File const & file, ifc::AttrIndex attribute, std::string_view attr_text)
    {
        ASSERT_EQ(attribute.sort(), ifc::AttrSort::Basic);
        auto word = file.basic_attributes()[attribute].word;
        ASSERT_EQ(word.sort, ifc::WordSort::Identifier);
        ASSERT_EQ(file.get_string(static_cast<ifc::TextOffset>(word.index)), attr_text);
    }

    void check_attribute(ifc::File const & file, ifc::DeclIndex decl, std::string_view attr_name)
    {
        const auto attributes = file.trait_declaration_attributes(decl);
        ASSERT_EQ(attributes.size(), 1);
        check_identifier_attribute(file, attributes[0], attr_name);
    }
}

TEST(SimpleTest, attributes)
{
    const auto file = FileWrapper::create("attributes.ixx.ifc");

    const auto top_level_declarations = get_declarations(file, file.global_scope());
    ASSERT_EQ(top_level_declarations.size(), 5);

    {
        const auto decl = top_level_declarations[ifc::Index{0}].index;
        auto const& function = file.functions()[decl];
        ASSERT_EQ(file.get_identifier(function.name), "a");
        check_attribute(file, decl, "noreturn");
    }

    {
        const auto decl = top_level_declarations[ifc::Index{1}].index;
        auto const& function = file.functions()[decl];
        ASSERT_EQ(file.get_identifier(function.name), "b");
        check_attribute(file, decl, "nodiscard");
    }

    {
        const auto decl = top_level_declarations[ifc::Index{2}].index;
        auto const& variable = file.variables()[decl];
        ASSERT_EQ(file.get_identifier(variable.name), "c");
        check_attribute(file, decl, "maybe_unused");
    }

    {
        const auto decl = top_level_declarations[ifc::Index{3}].index;
        auto const& scope = file.scope_declarations()[decl];
        ASSERT_EQ(file.get_identifier(scope.name), "d");
        ASSERT_EQ(get_kind(scope, file), ifc::TypeBasis::Struct);
        check_attribute(file, decl, "deprecated");
    }

    {
        const auto decl = top_level_declarations[ifc::Index{4}].index;
        auto const& scope = file.scope_declarations()[decl];
        ASSERT_EQ(file.get_identifier(scope.name), "e");
        ASSERT_EQ(get_kind(scope, file), ifc::TypeBasis::Class);
        const auto attributes = file.trait_declaration_attributes(decl);
        ASSERT_EQ(attributes.size(), 1);
        const auto attribute = file.called_attributes()[attributes[0]];
        check_identifier_attribute(file, attribute.function, "deprecated");
        check_identifier_attribute(file, attribute.arguments, "use class 'f' instead");
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
