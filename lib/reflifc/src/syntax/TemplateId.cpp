#include "reflifc/syntax/TemplateId.h"

#include "reflifc/Syntax.h"
#include "reflifc/TupleView.h"

#include <ifc/File.h>
#include <ifc/SyntaxTree.h>

namespace reflifc
{
    Syntax TemplateIdSyntax::name() const
    {
        return { ifc_, syntax_.name };
    }

    TupleSyntaxView TemplateIdSyntax::arguments() const
    {
        return { ifc_, ifc_.template_argument_list_syntax_trees()[syntax_.arguments].arguments };
    }
}
