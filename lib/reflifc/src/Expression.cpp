module reflifc;

import reflifc.Literal;
import reflifc.StringLiteral;

namespace reflifc
{
    bool Expression::is_monad() const
    {
        return sort() == ifc::ExprSort::Monad;
    }

    MonadExpression Expression::as_monad() const
    {
        return { ifc_, ifc_->monad_expressions()[index_] };
    }

    bool Expression::is_dyad() const
    {
        return sort() == ifc::ExprSort::Dyad;
    }

    DyadExpression Expression::as_dyad() const
    {
        return { ifc_, ifc_->dyad_expressions()[index_] };
    }

    bool Expression::is_unqualified_id() const
    {
        return sort() == ifc::ExprSort::UnqualifiedId;
    }

    UnqualifiedIdExpression Expression::as_unqualified_id() const
    {
        return { ifc_, ifc_->unqualified_id_expressions()[index_] };
    }

    bool Expression::is_qualified_name() const
    {
        return sort() == ifc::ExprSort::QualifiedName;
    }

    QualifiedNameExpression Expression::as_qualified_name() const
    {
        return { ifc_, ifc_->qualified_name_expressions()[index_] };
    }

    bool Expression::is_call() const
    {
        return sort() == ifc::ExprSort::Call;
    }

    CallExpression Expression::as_call() const
    {
        return { ifc_, ifc_->call_expressions()[index_] };
    }

    bool Expression::is_literal() const
    {
        return sort() == ifc::ExprSort::Literal;
    }

    Literal Expression::as_literal() const
    {
        return { ifc_, ifc_->literal_expressions()[index_].value };
    }

    bool Expression::is_string_literal() const
    {
        return sort() == ifc::ExprSort::String;
    }

    StringLiteral Expression::as_string_literal() const
    {
        return { ifc_, ifc_->string_literal_expressions()[ifc_->string_expressions()[index_].string_index] };
    }

    bool Expression::is_type() const
    {
        return sort() == ifc::ExprSort::Type;
    }

    Type Expression::as_type() const
    {
        return { ifc_, ifc_->type_expressions()[index_].denotation };
    }

    bool Expression::is_read() const
    {
        return sort() == ifc::ExprSort::Read;
    }

    ReadExpression Expression::as_read() const
    {
        return { ifc_, ifc_->read_expressions()[index_] };
    }

    bool Expression::is_template_id() const
    {
        return sort() == ifc::ExprSort::TemplateId;
    }

    TemplateId Expression::as_template_id() const
    {
        return { ifc_, ifc_->template_ids()[index_] };
    }

    bool Expression::is_template_reference() const
    {
        return sort() == ifc::ExprSort::TemplateReference;
    }

    TemplateReference Expression::as_template_reference() const
    {
        return { ifc_, ifc_->template_references()[index_] };
    }

    bool Expression::is_path() const
    {
        return sort() == ifc::ExprSort::Path;
    }

    PathExpression Expression::as_path() const
    {
        return { ifc_, ifc_->path_expressions()[index_] };
    }

    bool Expression::is_qualref() const
    {
        return sort() == ifc::ExprSort::NamedDecl;
    }

    Declaration Expression::referenced_decl() const
    {
        return { ifc_, ifc_->decl_expressions()[index_].resolution };
    }

    Syntax Expression::syntax() const
    {
        return { ifc_, ifc_->syntax_tree_expressions()[index_].syntax };
    }

    Expression Expression::packed_template_arguments() const
    {
        return { ifc_, ifc_->packed_template_arguments()[index_].arguments };
    }

    SizeofExpression Expression::as_sizeof() const
    {
        return { ifc_, ifc_->sizeof_expressions()[index_] };
    }

    AlignofExpression Expression::as_alignof() const
    {
        return { ifc_, ifc_->alignof_expressions()[index_] };
    }

    bool Expression::is_requires() const
    {
        return sort() == ifc::ExprSort::Requires;
    }

    RequiresExpression Expression::as_requires() const
    {
        return { ifc_, ifc_->requires_expressions()[index_] };
    }

    bool Expression::is_product_value_type() const
    {
        return sort() == ifc::ExprSort::ProductTypeValue;
    }

    ProductValueTypeExpression Expression::as_product_value_type() const
    {
        return { ifc_, ifc_->product_value_type_expressions()[index_] };
    }
}
