#include "Presenter.h"

#include "ifc/File.h"

void Presenter::present(ifc::NameIndex name) const
{
    using enum ifc::NameSort;

    switch (const auto kind = name.sort())
    {
    case Identifier:
        out_ << file_.get_string(ifc::TextOffset{name.index});
        break;
    case Operator:
        const auto operator_function_name = file_.operator_names()[name.index];
        out_ << "operator" << file_.get_string(operator_function_name.encoded);
        break;
    default:
        out_ << "Unsupported NameSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::FunctionType const& function_type) const
{
    present(function_type.target);
    out_ << "(";
    present(function_type.source);
    out_ << ")";
}

void Presenter::present(ifc::FundamentalType const& type) const
{
    using enum ifc::TypeBasis;
    switch (type.basis)
    {
    case Void:
        out_ << "void";
        break;
    case Bool:
        out_ << "bool";
        break;
    case Char:
        out_ << "char";
        break;
    case Wchar_t:
        out_ << "wchar_t";
        break;
    case Int:
        out_ << "int";
        break;
    case Float:
        out_ << "float";
        break;
    case Double:
        out_ << "double";
        break;
    default:
        out_ << "fundamental type {" << static_cast<int>(type.basis) << "}";
    }
}

void Presenter::present(ifc::TupleType tuple) const
{
    auto type_heap = file_.type_heap();
    bool first = true;
    for (size_t i = 0, n = raw_count(tuple.cardinality); i != n; ++i)
    {
        if (first)
            first = false;
        else
            out_ << ", ";
        present(type_heap[tuple.start + i]);
    }
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
    using enum ifc::Qualifiers;

    if (has_qualifier(quals, Const))
        out_ << "const ";
    if (has_qualifier(quals, Volatile))
        out_ << "volatile ";
    if (has_qualifier(quals, Restrict))
        out_ << "__restrict ";
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
    using enum ifc::DeclSort;

    switch (auto const kind = decl.resolution.sort())
    {
    case Reference:
        present(file_.decl_references()[decl.resolution.index]);
        break;
    default:
        out_ << "Declaration of unsupported kind '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::TupleExpression const& tuple) const
{
    auto expr_heap = file_.expr_heap();
    bool first = true;
    for (size_t i = 0, n = raw_count(tuple.cardinality); i != n; ++i)
    {
        if (first)
            first = false;
        else
            out_ << ", ";
        present(expr_heap[tuple.start + i]);
    }
}

void Presenter::present(ifc::ExprIndex expr) const
{
    using enum ifc::ExprSort;
    switch (auto const expr_kind = expr.sort())
    {
    case Type:
        present(file_.type_expressions()[expr.index].denotation);
        break;
    case NamedDecl:
        present(file_.decl_expressions()[expr.index]);
        break;
    case Tuple:
        present(file_.tuple_expressions()[expr.index]);
        break;
    default:
        out_ << "Unsupported ExprSort'" << static_cast<int>(expr_kind) << "'";
    }
}

void Presenter::present(ifc::TemplateId const& template_id) const
{
    present(template_id.primary);
    out_ << '<';
    present(template_id.arguments);
    out_ << '>';
}

void Presenter::present(ifc::SyntacticType type) const
{
    using enum ifc::ExprSort;
    switch (auto const expr_kind = type.expr.sort())
    {
    case TemplateId:
        present(file_.template_ids()[type.expr.index]);
        break;
    default:
        out_ << "Syntactic Type of unsupported expression kind '" << static_cast<int>(expr_kind) << "'";
    }
}

void Presenter::present(ifc::TypeIndex type) const
{
    using enum ifc::TypeSort;
    switch (const auto kind = type.sort())
    {
    case Fundamental:
        present(file_.fundamental_types()[type.index]);
        break;
    case Designated:
        present_refered_declaration(file_.designated_types()[type.index].decl);
        break;
    case Syntactic:
        present(file_.syntactic_types()[type.index]);
        break;
    case LvalueReference:
        present(file_.lvalue_references()[type.index]);
        break;
    case RvalueReference:
        present(file_.rvalue_references()[type.index]);
        break;
    case Function:
        present(file_.function_types()[type.index]);
        break;
    case Qualified:
        present(file_.qualified_types()[type.index]);
        break;
    case Tuple:
        present(file_.tuple_types()[type.index]);
        break;
    default:
        out_ << "Unsupported TypeSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present_refered_declaration(ifc::DeclIndex decl) const
{
    using enum ifc::DeclSort;

    switch (const auto kind = decl.sort())
    {
    case Parameter:
        {
            ifc::ParameterDeclaration const & param = file_.parameters()[decl.index];
            out_ << file_.get_string(param.name);
        }
        break;
    case Scope:
        {
            ifc::ScopeDeclaration const & scope = file_.scope_declarations()[decl.index];
            present(scope.name);
        }
        break;
    case Template:
        {
            ifc::TemplateDeclaration const & template_declaration = file_.template_declarations()[decl.index];
            present(template_declaration.name);
        }
        break;
    case Function:
        {
            ifc::FunctionDeclaration const & function = file_.functions()[decl.index];
            present(function.name);
        }
        break;
    case Reference:
        present(file_.decl_references()[decl.index]);
        break;
    default:
        out_ << "Unsupported DeclSort '" << static_cast<int>(kind) << "'";
    }
}

void Presenter::present(ifc::DeclIndex decl) const
{
    using enum ifc::DeclSort;

    switch (const auto kind = decl.sort())
    {
    case VendorExtension:
        out_ << "Vendor Extension\n";
        break;
    case Variable:
        {
            ifc::VariableDeclaration const & variable = file_.variables()[decl.index];
            out_ << "Variable '";
            present(variable.name);
            out_ << "'\n";
        }
        break;
    case Scope:
        {
            ifc::ScopeDeclaration const & scope = file_.scope_declarations()[decl.index];
            const auto type = scope.type;
            assert(type.sort() == ifc::TypeSort::Fundamental);
            switch (const auto scope_kind = file_.fundamental_types()[type.index].basis)
            {
                using enum ifc::TypeBasis;
            case Class:
                out_ << "Class";
                break;
            case Struct:
                out_ << "Struct";
                break;
            case Union:
                out_ << "Union";
                break;
            case Namespace:
                out_ << "Namespace";
                break;
            case Interface:
                out_ << "__interface";
                break;
            default:
                out_ << "Unknown Scope '" << static_cast<int>(scope_kind) << "'";
            }
            out_ << " '";
            present(scope.name);
            out_ << "'\n";
        }
        break;
    case Enumeration:
        {
            auto const & enumeration = file_.enumerations()[decl.index];
            out_ << "Enumeration '" << file_.get_string(enumeration.name) << "'\n";
        }
        break;
    case Alias:
        {
            auto const & alias = file_.alias_declarations()[decl.index];
            out_ << "Alias '" << file_.get_string(alias.name) << "'\n";
            break;
        }
    case Template:
        {
            auto const & template_declaration = file_.template_declarations()[decl.index];
            out_ << "Template ";
            present(template_declaration.entity.decl);
            out_ << "\n";
        }
        break;
    case Function:
        {
            ifc::FunctionDeclaration const & function = file_.functions()[decl.index];
            out_ << "Function '";
            present(function.name);
            out_ << "', type: ";
            present(function.type);
            out_ << "\n";
        }
        break;
    case UsingDeclaration:
        {
            auto const & using_declaration = file_.using_declarations()[decl.index];
            out_ << "Using '";
            present_refered_declaration(using_declaration.resolution);
            out_ << "'\n";
        }
        break;
    default:
        out_ << "Unsupported DeclSort '" << static_cast<int>(kind) << "'\n";
    }
}
