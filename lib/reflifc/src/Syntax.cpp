#include "reflifc/Syntax.h"

#include "reflifc/syntax/TemplateId.h"
#include "reflifc/syntax/TypeId.h"
#include "reflifc/syntax/TypeSpecifier.h"
#include "reflifc/syntax/TypeTraitIntrinsic.h"

#include "reflifc/Expression.h"

#include <ifc/File.h>
#include <ifc/SyntaxTree.h>

namespace reflifc
{
    TemplateIdSyntax Syntax::as_template_id() const
    {
        return { ifc_, ifc_->templateid_syntax_trees()[index_] };
    }

    Expression Syntax::as_expression() const
    {
        return { ifc_, ifc_->expression_syntax_trees()[index_].expression };
    }

    TypeIdSyntax Syntax::as_type_id() const
    {
        return { ifc_, ifc_->typeid_syntax_trees()[index_] };
    }

    TypeSpecifierSyntax Syntax::as_type_specifier() const
    {
        return { ifc_, ifc_->type_specifier_seq_syntax_trees()[index_] };
    }

    Syntax Syntax::as_type_template_argument() const
    {
        return { ifc_, ifc_->type_template_argument_syntax_trees()[index_].argument };
    }

    TypeTraitIntrinsicSyntax Syntax::as_type_trait_intrinsic() const
    {
        return { ifc_, ifc_->type_trait_intrinsic_syntax_trees()[index_] };
    }

    Expression Syntax::requires_clause_condition() const
    {
        return { ifc_, ifc_->requires_clause_syntax_trees()[index_].condition };
    }
}
