#include "Presenter.h"

#include "ifc/File.h"

#include "ifc/Chart.h"
#include "ifc/Expression.h"
#include "ifc/Declaration.h"
#include "ifc/SyntaxTree.h"
#include "ifc/Type.h"

#include <cassert>

void Presenter::present(ifc::NameIndex name) const
{
    switch (const auto kind = name.sort())
    {
    case ifc::NameSort::Identifier:
        out_ << file_.get_string(ifc::TextOffset{name.index});
        break;
    case ifc::NameSort::Operator:
        {
            const auto operator_function_name = file_.operator_names()[name];
            out_ << "operator" << file_.get_string(operator_function_name.encoded);
        }
        break;
    default:
        out_ << "Unsupported NameSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::FunctionType const& function_type) const
{
    present_function_type(function_type);
}

void Presenter::present(ifc::MethodType const& method_type) const
{
    present_function_type(method_type);
}

void Presenter::present_function_type(auto const& function_type) const
{
    present(function_type.target);
    out_ << "(";
    if (auto params = function_type.source; !params.is_null())
        present(params);
    out_ << ")";
    present(function_type.traits);
}

void Presenter::present(ifc::FunctionTypeTraits traits) const
{
    if (has_trait(traits, ifc::FunctionTypeTraits::Const))
        out_ << " const";
    if (has_trait(traits, ifc::FunctionTypeTraits::Volatile))
        out_ << " volatile";
    if (has_trait(traits, ifc::FunctionTypeTraits::Lvalue))
        out_ << " &";
    if (has_trait(traits, ifc::FunctionTypeTraits::Rvalue))
        out_ << " &&";
}

void Presenter::present(ifc::FundamentalType const& type) const
{
    switch (type.sign)
    {
    case ifc::TypeSign::Plain:
        break;
    case ifc::TypeSign::Signed:
        out_ << "signed ";
        break;
    case ifc::TypeSign::Unsigned:
        out_ << "unsigned ";
        break;
    }

    switch (type.precision)
    {
    case ifc::TypePrecision::Default:
        break;
    case ifc::TypePrecision::Short:
        assert(type.basis == ifc::TypeBasis::Int);
        out_ << "short";
        return;
    case ifc::TypePrecision::Long:
        out_ << "long ";
        break;
    case ifc::TypePrecision::Bit64:
        assert(type.basis == ifc::TypeBasis::Int);
        out_ << "long long";
        return;
    case ifc::TypePrecision::Bit8:
        if (type.basis == ifc::TypeBasis::Char)
        {
            out_ << "char8_t";
            return;
        }
    case ifc::TypePrecision::Bit16:
        if (type.basis == ifc::TypeBasis::Char)
        {
            out_ << "char16_t";
            return;
        }
    case ifc::TypePrecision::Bit32:
        if (type.basis == ifc::TypeBasis::Char)
        {
            out_ << "char32_t";
            return;
        }
    case ifc::TypePrecision::Bit128:
        out_ << "Unsupported Bitness '" << static_cast<int>(type.precision) << "' ";
        break;
    }

    switch (type.basis)
    {
    case ifc::TypeBasis::Void:
        out_ << "void";
        break;
    case ifc::TypeBasis::Bool:
        out_ << "bool";
        break;
    case ifc::TypeBasis::Char:
        out_ << "char";
        break;
    case ifc::TypeBasis::Wchar_t:
        out_ << "wchar_t";
        break;
    case ifc::TypeBasis::Int:
        out_ << "int";
        break;
    case ifc::TypeBasis::Float:
        out_ << "float";
        break;
    case ifc::TypeBasis::Double:
        out_ << "double";
        break;
    default:
        out_ << "fundamental type {" << static_cast<int>(type.basis) << "}";
    }
}

template<typename T, typename Index>
void Presenter::present_heap_slice(ifc::Partition<T, Index> heap, ifc::Sequence seq) const
{
    present_range(heap.slice(seq), ", ");
}

template<typename Range>
void Presenter::present_range(Range range, std::string_view separator) const
{
    bool first = true;
    for (auto element : range)
    {
        if (first)
            first = false;
        else
            out_ << separator;
        present(element);
    }
}

void Presenter::present(ifc::TupleType tuple) const
{
    present_heap_slice(file_.type_heap(), tuple);
}

void Presenter::present(ifc::LvalueReference ref) const
{
    present(ref.referee);
    out_ << "&";
}

void Presenter::present(ifc::RvalueReference ref) const
{
    present(ref.referee);
    out_ << "&&";
}

void Presenter::present(ifc::Qualifiers quals) const
{
    if (has_qualifier(quals, ifc::Qualifiers::Const))
        out_ << "const ";
    if (has_qualifier(quals, ifc::Qualifiers::Volatile))
        out_ << "volatile ";
    if (has_qualifier(quals, ifc::Qualifiers::Restrict))
        out_ << "__restrict ";
}

void Presenter::present(ifc::PlaceholderType placeholder) const
{
    switch (const auto basis = placeholder.basis)
    {
    case ifc::TypeBasis::Auto:
        out_ << "auto";
        break;
    case ifc::TypeBasis::DecltypeAuto:
        out_ << "delctype(auto)";
        break;
    default:
        out_ << "Unexpected placeholder basis: " << static_cast<int>(basis);
    }
}

void Presenter::present(ifc::QualifiedType qualType) const
{
    present(qualType.qualifiers);
    present(qualType.unqualified);
}

void Presenter::present(ifc::DeclReference decl_ref) const
{
    ifc::File const & imported_module = file_.get_imported_module(decl_ref.unit);
    Presenter(imported_module, out_).present_refered_declaration(decl_ref.local_index);
}

void Presenter::present(ifc::NamedDecl const& decl) const
{
    switch (auto const kind = decl.resolution.sort())
    {
    case ifc::DeclSort::Reference:
        present(file_.decl_references()[decl.resolution]);
        break;
    case ifc::DeclSort::Template:
        present(file_.template_declarations()[decl.resolution].name);
        break;
    default:
        out_ << "Declaration of unsupported kind '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::UnqualifiedId const& expr) const
{
    present(expr.name);
}

void Presenter::present(ifc::TupleExpression const& tuple) const
{
    present_heap_slice(file_.expr_heap(), tuple.seq);
}

void Presenter::present(ifc::ExprIndex expr) const
{
    switch (auto const expr_kind = expr.sort())
    {
    case ifc::ExprSort::Literal:
        present(file_.literal_expressions()[expr].value);
        break;
    case ifc::ExprSort::Type:
        present(file_.type_expressions()[expr].denotation);
        break;
    case ifc::ExprSort::NamedDecl:
        present(file_.decl_expressions()[expr]);
        break;
    case ifc::ExprSort::UnqualifiedId:
        present(file_.unqualified_id_expressions()[expr]);
        break;
    case ifc::ExprSort::Dyad:
        present(file_.dyad_expressions()[expr]);
        break;
    case ifc::ExprSort::SizeofType:
        present(file_.sizeof_expressions()[expr]);
        break;
    case ifc::ExprSort::Alignof:
        present(file_.alignof_expressions()[expr]);
        break;
    case ifc::ExprSort::Tuple:
        present(file_.tuple_expressions()[expr]);
        break;
    case ifc::ExprSort::PackedTemplateArguments:
        present(file_.packed_template_arguments()[expr]);
        break;
    default:
        out_ << "Unsupported ExprSort'" << static_cast<int>(expr_kind) << "'";
    }
}

void Presenter::present(ifc::ChartIndex chart) const
{
    switch (chart.sort())
    {
    case ifc::ChartSort::None:
        out_ << "template<> ";
        break;
    case ifc::ChartSort::Unilevel:
        {
            auto uni_chart = file_.unilevel_charts()[chart];
            out_ << "template<";
            bool first = true;
            for (auto param : file_.parameters().slice(uni_chart))
            {
                if (first)
                    first = false;
                else
                    out_ << ", ";
                switch (param.sort)
                {
                case ifc::ParameterSort::Object:
                    assert(false && "function parameter is unexpected here");
                    break;
                case ifc::ParameterSort::Type:
                    out_ << "typename";
                    break;
                case ifc::ParameterSort::NonType:
                    present(param.type);
                    break;
                case ifc::ParameterSort::Template:
                    assert(param.type.sort() == ifc::TypeSort::Forall);
                    auto forall_type = file_.forall_types()[param.type];
                    assert(forall_type.chart.sort() == ifc::ChartSort::Unilevel);
                    present(forall_type.chart);
                    assert(forall_type.subject.sort() == ifc::TypeSort::Fundamental);
                    assert(file_.fundamental_types()[forall_type.subject].basis == ifc::TypeBasis::Typename);
                    out_ << "typename";
                    break;
                }
                if (param.pack)
                    out_ << "...";
                if (!is_null(param.name))
                    out_ << " " << file_.get_string(param.name);
            }
            out_ << "> ";
        }
        break;
    case ifc::ChartSort::Multilevel:
        out_ << "Chart.Multilevel presentation is unsupported ";
        break;
    }
}

void Presenter::present(ifc::TemplateId const& template_id) const
{
    present(template_id.primary);
    out_ << '<';
    present(template_id.arguments);
    out_ << '>';
}

void Presenter::present(ifc::DyadExpression const& dyad) const
{
    present(dyad.arguments[0]);
    out_ << " " << to_string(dyad.op) << " ";
    present(dyad.arguments[1]);
}

void Presenter::present(ifc::SizeofExpression const& expr) const
{
    out_ << "sizeof(";
    present(expr.operand);
    out_ << ")";
}

void Presenter::present(ifc::AlignofExpression const& expr) const
{
    out_ << "alignof(";
    present(expr.operand);
    out_ << ")";
}

void Presenter::present(ifc::PackedTemplateArguments const& templargs) const
{
    present(templargs.arguments);
}

void Presenter::present(ifc::LitIndex lit) const
{
    switch (lit.sort())
    {
    case ifc::LiteralSort::Immediate:
        out_ << lit.index;
        break;
    case ifc::LiteralSort::Integer:
        out_ << file_.integer_literals()[lit].value;
        break;
    case ifc::LiteralSort::FloatingPoint:
        out_ << file_.fp_literals()[lit].value();
        break;
    default: ;
    }

}

void Presenter::present(ifc::SyntacticType type) const
{
    switch (auto const expr_kind = type.expr.sort())
    {
    case ifc::ExprSort::TemplateId:
        present(file_.template_ids()[type.expr]);
        break;
    default:
        out_ << "Syntactic Type of unsupported expression kind '" << static_cast<int>(expr_kind) << "'";
    }
}

void Presenter::present(ifc::ExpansionType type) const
{
    present(type.pack);
    out_ << "...";
}

void Presenter::present(ifc::PointerType pointer) const
{
    present(pointer.pointee);
    out_ << "*";
}

void Presenter::present(ifc::TypeIndex type) const
{
    switch (const auto kind = type.sort())
    {
    case ifc::TypeSort::Fundamental:
        present(file_.fundamental_types()[type]);
        break;
    case ifc::TypeSort::Designated:
        present_refered_declaration(file_.designated_types()[type].decl);
        break;
    case ifc::TypeSort::Syntactic:
        present(file_.syntactic_types()[type]);
        break;
    case ifc::TypeSort::Expansion:
        present(file_.expansion_types()[type]);
        break;
    case ifc::TypeSort::Pointer:
        present(file_.pointer_types()[type]);
        break;
    case ifc::TypeSort::LvalueReference:
        present(file_.lvalue_references()[type]);
        break;
    case ifc::TypeSort::RvalueReference:
        present(file_.rvalue_references()[type]);
        break;
    case ifc::TypeSort::Function:
        present(file_.function_types()[type]);
        break;
    case ifc::TypeSort::Method:
        present(file_.method_types()[type]);
        break;
    case ifc::TypeSort::Qualified:
        present(file_.qualified_types()[type]);
        break;
    case ifc::TypeSort::Base:
        present(file_.base_types()[type]);
        break;
    case ifc::TypeSort::Tuple:
        present(file_.tuple_types()[type]);
        break;
    case ifc::TypeSort::SyntaxTree:
        present(file_.syntax_types()[type].syntax);
        break;
    case ifc::TypeSort::Placeholder:
        present(file_.placeholder_types()[type]);
        break;
    default:
        out_ << "Unsupported TypeSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::BaseType const& base) const
{
    switch (base.access)
    {
    case ifc::Access::None:
        break;
    case ifc::Access::Private:
        out_ << "private ";
        break;
    case ifc::Access::Protected:
        out_ << "protected ";
        break;
    case ifc::Access::Public:
        out_ << "public ";
        break;
    }
    if (base.specifiers & ifc::BaseType::Shared)
        out_ << "virtual ";
    present(base.type);
    if (base.specifiers & ifc::BaseType::Expanded)
        out_ << "...";
}

void Presenter::present_refered_declaration(ifc::DeclIndex decl) const
{
    switch (const auto kind = decl.sort())
    {
    case ifc::DeclSort::Parameter:
        {
            ifc::ParameterDeclaration const & param = file_.parameters()[decl];
            out_ << file_.get_string(param.name);
        }
        break;
    case ifc::DeclSort::Scope:
        {
            ifc::ScopeDeclaration const & scope = get_scope(file_, decl);
            present(scope.name);
        }
        break;
    case ifc::DeclSort::Template:
        {
            ifc::TemplateDeclaration const & template_declaration = file_.template_declarations()[decl];
            present(template_declaration.name);
        }
        break;
    case ifc::DeclSort::Function:
        {
            ifc::FunctionDeclaration const & function = file_.functions()[decl];
            present(function.name);
        }
        break;
    case ifc::DeclSort::Reference:
        present(file_.decl_references()[decl]);
        break;
    case ifc::DeclSort::Enumeration:
        {
            auto const & enumeration = file_.enumerations()[decl];
            out_ << file_.get_string(enumeration.name);
        }
        break;
    default:
        out_ << "Unsupported DeclSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present_scope_members(ifc::ScopeDescriptor scope) const
{
    present_range(get_declarations(file_, scope), "\n");
}

void Presenter::present(ifc::ScopeDeclaration const& scope) const
{
    const auto type = scope.type;
    assert(type.sort() == ifc::TypeSort::Fundamental);
    switch (const auto scope_kind = get_kind(scope, file_))
    {
    case ifc::TypeBasis::Class:
        out_ << "Class";
        break;
    case ifc::TypeBasis::Struct:
        out_ << "Struct";
        break;
    case ifc::TypeBasis::Union:
        out_ << "Union";
        break;
    case ifc::TypeBasis::Namespace:
        out_ << "Namespace";
        break;
    case ifc::TypeBasis::Interface:
        out_ << "__interface";
        break;
    default:
        out_ << "Unknown Scope '" << static_cast<int>(scope_kind) << "'";
    }
    out_ << " '";
    present(scope.name);
    out_ << "'";
    if (auto const base = scope.base; !base.is_null())
    {
        out_ << " : ";
        present(base);
    }
    if (auto const def = scope.initializer; is_null(def))
    {
        out_ << ": incomplete";
    }
    else
    {
        out_ << " {\n";
        indent_ += 2;
        present_scope_members(file_.scope_descriptors()[def]);
        indent_ -= 2;

        insert_indent();
        out_ << "}";
    }
    out_ << "\n";
}

void Presenter::present(ifc::FunctionDeclaration const& function) const
{
    out_ << "Function '";
    present(function.name);
    out_ << "', type: ";
    present(function.type);
    out_ << "\n";
}

void Presenter::present(ifc::MethodDeclaration const& method) const
{
    out_ << "Method '";
    present(method.name);
    out_ << "', type: ";
    present(method.type);
    out_ << "\n";
}

namespace SpecialMemberNames
{
    using namespace std::string_view_literals;

    constexpr auto Ctor = "{ctor}"sv;
    constexpr auto Dtor = "{dtor}"sv;
}

void Presenter::present(ifc::Constructor const& constructor) const
{
    assert(file_.get_string(constructor.name) == SpecialMemberNames::Ctor);
    assert(constructor.type.sort() == ifc::TypeSort::Tor);
    auto type = file_.tor_types()[constructor.type];
    if (auto params = type.source; params.is_null())
    {
        out_ << "Default Constructor";
    }
    else
    {
        out_ << "Constructor, parameter types: (";
        present(type.source);
        out_ << ")";
    }
    out_ << "\n";
}

void Presenter::present(ifc::Destructor const& destructor) const
{
    assert(file_.get_string(destructor.name) == SpecialMemberNames::Dtor);
    out_ << "Destructor\n";
}

void Presenter::present(ifc::VariableDeclaration const& variable) const
{
    out_ << "Variable '";
    present(variable.name);
    out_ << "'";
    if (const auto initializer = variable.initializer; !initializer.is_null())
    {
        out_ << " = ";
        present(variable.initializer);
    }
    out_ << ", type: ";
    present(variable.type);
    out_ << "\n";
}

void Presenter::present(ifc::FieldDeclaration const& field) const
{
    out_ << "Field '" << file_.get_string(field.name) << "' type: ";
    present(field.type);
    out_ << "\n";
}

void Presenter::present(ifc::TemplateDeclaration const& template_) const
{
    present(template_.chart);
    out_ << "\n";
    present(template_.entity.decl);
}

void Presenter::present(ifc::Enumeration const& enumeration) const
{
    out_ << "Enumeration '" << file_.get_string(enumeration.name) << "' {\n";
    indent_ += 2;
    for (ifc::Enumerator const & enumerator : file_.enumerators().slice(enumeration.initializer))
    {
        insert_indent();
        out_ << file_.get_string(enumerator.name) << "\n";
    }
    indent_ -= 2;

    insert_indent();
    out_ << "}\n";
}

void Presenter::present(ifc::AliasDeclaration const& alias) const
{
    out_ << "Alias '" << file_.get_string(alias.name) << "'\n";
}

void Presenter::present(ifc::UsingDeclaration const& using_declaration) const
{
    out_ << "Using '";
    present_refered_declaration(using_declaration.resolution);
    out_ << "'\n";
}

void Presenter::present(ifc::Concept const& concept_) const
{
    present(concept_.chart);
    out_ << "\n";
    insert_indent();
    out_ << "Concept '" << file_.get_string(concept_.name) << "' = ";
    present(concept_.constraint);
    out_ << "\n";
}

void Presenter::present(ifc::SyntaxIndex syntax) const
{
    switch (auto const kind = syntax.sort())
    {
    case ifc::SyntaxSort::SimpleTypeSpecifier:
        present(file_.simple_type_specifiers()[syntax]);
        break;
    case ifc::SyntaxSort::TypeSpecifierSeq:
        present(file_.type_specifier_seq_syntax_trees()[syntax]);
        break;
    case ifc::SyntaxSort::TypeId:
        present(file_.typeid_syntax_trees()[syntax]);
        break;
    case ifc::SyntaxSort::Declarator:
        present(file_.declarator_syntax_trees()[syntax]);
        break;
    case ifc::SyntaxSort::PointerDeclarator:
        present(file_.pointer_declarator_syntax_trees()[syntax]);
        break;
    case ifc::SyntaxSort::Expression:
        present(file_.expression_syntax_trees()[syntax].expression);
        break;
    default:
        out_ << "Unsupported SyntaxSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::SimpleTypeSpecifier const& specifier) const
{
    out_ << "simple-type-specifier";
}

void Presenter::present(ifc::TypeIdSyntax const& type_id) const
{
    present(type_id.type_specifier);
    if (auto decl = type_id.abstract_declarator; !decl.is_null())
    {
        assert(decl.sort() == ifc::SyntaxSort::Declarator);
        present(file_.declarator_syntax_trees()[decl]);
    }
}

void Presenter::present(ifc::DeclaratorSyntax const& declarator) const
{
    if (auto ptr = declarator.pointer; !ptr.is_null())
    {
        assert(ptr.sort() == ifc::SyntaxSort::PointerDeclarator);
        present(file_.pointer_declarator_syntax_trees()[ptr]);
    }
    else
        out_ << "Unsupported declarator-syntax-tree";
}

void Presenter::present(ifc::PointerDeclaratorSyntax const& pointer) const
{
    switch (const auto kind = pointer.sort)
    {
    case ifc::PointerDeclaratorSort::Pointer:
        out_ << "*";
        break;
    case ifc::PointerDeclaratorSort::LvalueReference:
        out_ << "&";
        break;
    case ifc::PointerDeclaratorSort::RvalueReference:
        out_ << "&&";
        break;
    default:
        out_ << "Unsupported PointerDeclarator '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::TypeSpecifierSeq const& seq) const
{
    present(seq.qualifiers);
    if (auto typename_ =  seq.typename_; !typename_.is_null())
        present(typename_);
    else
        present(seq.type);
}

void Presenter::insert_indent() const
{
    for (size_t i = 0; i != indent_; ++i)
        out_ << ' ';
}

void Presenter::present(ifc::DeclIndex decl) const
{
    insert_indent();

    if (auto attr_index = file_.trait_declaration_attributes(decl))
    {
        out_ << "Found a attribute!!!";
    }

    switch (const auto kind = decl.sort())
    {
    case ifc::DeclSort::VendorExtension:
        out_ << "Vendor Extension\n";
        break;
    case ifc::DeclSort::Variable:
        present(file_.variables()[decl]);
        break;
    case ifc::DeclSort::Field:
        present(file_.fields()[decl]);
        break;
    case ifc::DeclSort::Scope:
        present(get_scope(file_, decl));
        break;
    case ifc::DeclSort::Enumeration:
        present(file_.enumerations()[decl]);
        break;
    case ifc::DeclSort::Alias:
        present(file_.alias_declarations()[decl]);
        break;
    case ifc::DeclSort::Template:
        present(file_.template_declarations()[decl]);
        break;
    case ifc::DeclSort::Concept:
        present(file_.concepts()[decl]);
        break;
    case ifc::DeclSort::Function:
        present(file_.functions()[decl]);
        break;
    case ifc::DeclSort::Method:
        present(file_.methods()[decl]);
        break;
    case ifc::DeclSort::Constructor:
        present(file_.constructors()[decl]);
        break;
    case ifc::DeclSort::Destructor:
        present(file_.destructors()[decl]);
        break;;
    case ifc::DeclSort::UsingDeclaration:
        present(file_.using_declarations()[decl]);
        break;
    default:
        out_ << "Unsupported DeclSort '" << static_cast<int>(kind) << "'\n";
    }
}

void Presenter::present(ifc::Declaration decl) const
{
    present(decl.index);
}
