#include "reflifc/syntax/TypeSpecifier.h"

#include "reflifc/Syntax.h"

#include <ifc/SyntaxTree.h>

namespace reflifc
{
    Syntax TypeSpecifierSyntax::typename_() const
    {
        return { ifc_, syntax_->typename_ };
    }
}
