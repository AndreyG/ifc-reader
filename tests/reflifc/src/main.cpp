#include "reflifc/Module.h"
#include "reflifc/Expression.h"
#include "reflifc/Query.h"
#include "reflifc/TemplateId.h"
#include "reflifc/Type.h"
#include "reflifc/TupleView.h"
#include "reflifc/Word.h"
#include "reflifc/decl/Function.h"
#include "reflifc/decl/Variable.h"
#include "reflifc/decl/Parameter.h"
#include "reflifc/decl/TemplateDeclaration.h"
#include "reflifc/decl/Specialization.h"
#include "reflifc/expr/Call.h"
#include "reflifc/type/Function.h"
#include "reflifc/type/Base.h"
#include "reflifc/type/Pointer.h"

#include <ifc/blob_reader.h>

#include <gtest/gtest.h>

#include <filesystem>

static std::filesystem::path data_dir;

class ModuleWrapper
{
    ifc::Environment::BlobHolderPtr blob_;
    ifc::File file_;

public:
    reflifc::Module module;

    ModuleWrapper(std::filesystem::path const & path_to_ifc)
        : blob_(ifc::read_blob(path_to_ifc))
        , file_(blob_->view())
        , module(&file_)
    {}

public:
    static ModuleWrapper create(const char* filepath)
    {
        const auto path_to_ifc = data_dir / filepath;
        if (!is_regular_file(path_to_ifc))
            throw std::logic_error("'" + path_to_ifc.string() + "' is not regular file_");

        return ModuleWrapper(path_to_ifc);
    }
};

std::string_view get_identifier(ifc::File const& file, ifc::NameIndex name)
{
    return file.get_string(ifc::TextOffset{name.index});
}

namespace
{
    void check_identifier_attribute(reflifc::Attribute attribute, std::string_view attr_text)
    {
        ASSERT_TRUE(attribute.is_basic());
        auto word = attribute.as_basic();
        ASSERT_TRUE(word.is_identifier());
        ASSERT_EQ(word.as_identifier(), attr_text);
    }

    void check_attribute(reflifc::Declaration decl, std::string_view attr_name)
    {
        const auto attributes = decl.attributes();
        ASSERT_EQ(attributes.size(), 1);
        check_identifier_attribute(attributes[0], attr_name);
    }
}

TEST(SimpleTest, attributes)
{
    const auto wrapper = ModuleWrapper::create("attributes.ixx.ifc");
    auto module = wrapper.module;

    const auto top_level_declarations = module.global_namespace().get_declarations();
    ASSERT_EQ(top_level_declarations.size(), 5);

    {
        const auto decl = top_level_declarations[0];
        ASSERT_TRUE(has_name(decl.as_function(), "a"));
        check_attribute(decl, "noreturn");
    }

    {
        const auto decl = top_level_declarations[1];
        ASSERT_TRUE(has_name(decl.as_function(), "b"));
        check_attribute(decl, "nodiscard");
    }

    {
        const auto decl = top_level_declarations[2];
        ASSERT_TRUE(has_name(decl.as_variable(), "c"));
        check_attribute(decl, "maybe_unused");
    }

    {
        const auto decl = top_level_declarations[3];
        auto scope = decl.as_scope();
        ASSERT_TRUE(has_name(scope, "d"));
        ASSERT_TRUE(scope.is_class_or_struct());
        check_attribute(decl, "deprecated");
    }

    {
        const auto decl = top_level_declarations[4];
        auto scope = decl.as_scope();
        ASSERT_TRUE(has_name(scope, "e"));
        ASSERT_TRUE(scope.is_class_or_struct());
        const auto attributes = decl.attributes();
        ASSERT_EQ(attributes.size(), 1);
        const auto attribute = attributes.front().as_called();
        check_identifier_attribute(attribute.function(), "deprecated");
        check_identifier_attribute(attribute.arguments(), "use class 'f' instead");
    }
}

TEST(TupleExprView, empty)
{
    const auto wrapper = ModuleWrapper::create("tuple-expr-view-empty.ixx.ifc");
    auto module = wrapper.module;

    const auto top_level_declarations = module.global_namespace().get_declarations();
    ASSERT_EQ(top_level_declarations.size(), 1);

    const auto decl = top_level_declarations[0];
    ASSERT_TRUE(decl.is_template());

    const auto primary_template = decl.as_template().entity();
    ASSERT_TRUE(primary_template.is_variable());

    const auto variable = primary_template.as_variable();
    ASSERT_TRUE(is_identifier(variable.name(), "var"));

    const auto type = variable.type();
    ASSERT_TRUE(type.is_decltype());

    const auto decltype_argument = type.decltype_argument();
    ASSERT_TRUE(decltype_argument.is_call());

    const auto call_arguments = decltype_argument.as_call().arguments();
    ASSERT_TRUE(call_arguments.empty());
    ASSERT_EQ(call_arguments.size(), 0);
    ASSERT_EQ(call_arguments.begin(), call_arguments.end());
}

TEST(TupleExprView, single_element)
{
    const auto wrapper = ModuleWrapper::create("tuple-expr-view-single-element.ixx.ifc");
    auto module = wrapper.module;

    const auto top_level_declarations = module.global_namespace().get_declarations();
    ASSERT_EQ(top_level_declarations.size(), 1);

    const auto decl = top_level_declarations[0];
    ASSERT_TRUE(decl.is_template());

    const auto primary_template = decl.as_template().entity();
    ASSERT_TRUE(primary_template.is_function());

    const auto function = primary_template.as_function();
    ASSERT_TRUE(is_identifier(function.name(), "f"));

    const auto return_type = function.type().return_type();
    ASSERT_TRUE(return_type.is_decltype());

    const auto decltype_argument = return_type.decltype_argument();
    ASSERT_TRUE(decltype_argument.is_call());

    const auto call_arguments = decltype_argument.as_call().arguments();
    ASSERT_EQ(call_arguments.size(), 1);
    ASSERT_FALSE(call_arguments.begin() == call_arguments.end());

    const auto argument = call_arguments[0];
    ASSERT_TRUE(argument.is_unqualified_id());
}

TEST(Class, bases)
{
    const auto wrapper = ModuleWrapper::create("class-bases.ixx.ifc");
    auto module = wrapper.module;

    auto classes = get_classes_and_structs(module);
    auto it = classes.begin();

    {
        auto a = *it++;
        ASSERT_TRUE(is_identifier(a.name(), "A"));
        ASSERT_TRUE(a.bases().empty());
    }

    {
        auto b = *it++;
        auto bases = b.bases();
        ASSERT_EQ(bases.size(), 1);
        auto base = *bases.begin();
        ASSERT_EQ(base.specifiers, ifc::BaseType::Specifiers::Expanded);
        ASSERT_TRUE(base.type.is_designated());
        auto base_type = base.type.designation();
        ASSERT_TRUE(base_type.is_parameter());
        ASSERT_EQ(base_type.as_parameter().sort(), ifc::ParameterSort::Type);
    }

    {
        auto c = *it++;
        ASSERT_EQ(c.bases().size(), 3);
    }

    ASSERT_EQ(it, classes.end());
}

static void check_is_var_of_instantiation_type(reflifc::Declaration decl, std::string_view var_name, reflifc::Declaration type_primary_template)
{
    ASSERT_TRUE(decl.is_variable());
    auto var = decl.as_variable();
    ASSERT_TRUE(is_identifier(var.name(), var_name));
    auto type = var.type();
    ASSERT_TRUE(type.is_syntactic());
    auto syntactic_type = type.as_syntactic();
    ASSERT_TRUE(syntactic_type.is_template_id());
    ASSERT_EQ(syntactic_type.as_template_id().primary().referenced_decl(), type_primary_template);
}

using namespace std::string_view_literals;

TEST(Class, specialization)
{
    const auto wrapper = ModuleWrapper::create("class-specialization.ixx.ifc");
    auto declarations = wrapper.module.global_namespace().get_declarations();

    auto it = declarations.begin();

    const auto X_primary_template = *it++;
    ASSERT_TRUE(X_primary_template.is_template());

    {
        auto templ = X_primary_template.as_template();
        ASSERT_TRUE(is_identifier(templ.name(), "X"));
        ASSERT_TRUE(templ.entity().is_class_or_struct());
    }

    {
        auto decl = *it++;
        ASSERT_TRUE(decl.is_partial_specialization());
        auto spec = decl.as_partial_specialization();
        auto name = spec.name();
        ASSERT_TRUE(name.is_identifier());
        auto form = spec.form();
        ASSERT_EQ(form.primary_template(), X_primary_template);
        auto tempargs = form.arguments();
        ASSERT_EQ(tempargs.size(), 1);
        auto templarg = tempargs.front();
        ASSERT_TRUE(templarg.is_type());
        auto typearg = templarg.as_type();
        ASSERT_TRUE(typearg.is_pointer());
        auto pointee = typearg.as_pointer().pointee;
        ASSERT_TRUE(pointee.is_designated());
        auto designation = pointee.designation();
        ASSERT_TRUE(designation.is_parameter());
        ASSERT_EQ(designation.as_parameter().name(), "T"sv);
        auto entity = spec.entity();
        ASSERT_TRUE(entity.is_class_or_struct());
        ASSERT_TRUE(entity.as_class_or_struct().name() == name);
    }

    {
        auto decl = *it++;
        ASSERT_TRUE(decl.is_specialization());
        auto spec = decl.as_specialization();
        auto form = spec.form();
        ASSERT_EQ(form.primary_template(), X_primary_template);
        auto tempargs = form.arguments();
        ASSERT_EQ(tempargs.size(), 1);
        auto templarg = tempargs.front();
        ASSERT_TRUE(templarg.is_type());
        auto typearg = templarg.as_type();
        ASSERT_TRUE(typearg.is_fundamental());
        ASSERT_EQ(typearg.as_fundamental().basis, ifc::TypeBasis::Void);
        ASSERT_TRUE(spec.entity().is_class_or_struct());
        ASSERT_EQ(spec.sort(), ifc::SpecializationSort::Explicit);
    }

    check_is_var_of_instantiation_type(*it++, "x1", X_primary_template);
    check_is_var_of_instantiation_type(*it++, "x2", X_primary_template);
    check_is_var_of_instantiation_type(*it++, "x3", X_primary_template);

    ASSERT_EQ(it, declarations.end());
}

TEST(Expression, TemplateReference)
{
    const auto wrapper = ModuleWrapper::create("template-reference.ixx.ifc");
    auto declarations = wrapper.module.global_namespace().get_declarations();

    auto it = declarations.begin();

    const auto X = *it++;
    ASSERT_TRUE(X.is_template());

    auto templ = X.as_template();
    ASSERT_TRUE(is_identifier(templ.name(), "X"));
    ASSERT_TRUE(templ.entity().is_class_or_struct());

    auto decl = *it++;
    ASSERT_TRUE(decl.is_variable());
    auto var = decl.as_variable();
    ASSERT_TRUE(is_identifier(var.name(), "a"));
    auto type = var.type();
    ASSERT_TRUE(type.is_syntactic());
    auto syntactic_type = type.as_syntactic();
    ASSERT_TRUE(syntactic_type.is_template_reference());
    auto template_ref = syntactic_type.as_template_reference();
    auto member_name = template_ref.member_name();
    ASSERT_TRUE(is_identifier(member_name, "A"));
    ASSERT_TRUE(template_ref.arguments().empty());
    auto member = template_ref.member();
    ASSERT_TRUE(member.is_class_or_struct());
    auto member_class = member.as_class_or_struct();
    ASSERT_EQ(member_class.name(), member_name);
    ASSERT_EQ(member_class.home_scope(), X);
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
