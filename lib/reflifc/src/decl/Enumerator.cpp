#include "reflifc/decl/Enumerator.h"

#include "reflifc/Expression.h"

#include <ifc/Declaration.h>
#include <ifc/File.h>

namespace reflifc
{
    const char* Enumerator::name() const
    {
        return ifc_.get_string(enumerator_.name);
    }

    Expression Enumerator::value() const
    {
        return { ifc_, enumerator_.initializer };
    }
}
