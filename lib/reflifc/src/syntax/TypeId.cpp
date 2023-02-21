#include "reflifc/syntax/TypeId.h"
#include "reflifc/syntax/TypeSpecifier.h"

#include "reflifc/Syntax.h"

#include <ifc/SyntaxTree.h>

namespace reflifc
{
    TypeSpecifierSyntax TypeIdSyntax::type_specifier() const
    {
        return Syntax(ifc_, syntax_->type_specifier).as_type_specifier();
    }
}
