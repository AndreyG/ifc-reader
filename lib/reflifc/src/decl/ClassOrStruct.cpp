#include "reflifc/decl/ClassOrStruct.h"

#include "reflifc/Name.h"

namespace reflifc
{
    bool ClassOrStruct::is_complete() const
    {
        return !is_null(scope_.initializer);
    }

    Name ClassOrStruct::name() const
    {
        return { ifc_, scope_.name };
    }

    ifc::TypeBasis ClassOrStruct::kind() const
    {
        return ifc_.fundamental_types()[scope_.type].basis;
    }
}
