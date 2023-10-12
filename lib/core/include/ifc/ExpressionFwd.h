#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class ExprSort;
    using ExprIndex = AbstractReference<6, ExprSort>;

    enum class StringSort : uint8_t;
    using StringIndex = AbstractReference<3, StringSort>;

    struct LiteralExpression;
    struct TupleExpression;
    struct ExpressionListExpression;
    struct TemplateId;
    struct TemplateReference;
    struct NamedDecl;
    struct UnqualifiedId;
    struct TypeExpression;
    struct MonadExpression;
    struct DyadExpression;
    struct StringExpression;
    struct CallExpression;
    struct SizeofExpression;
    struct AlignofExpression;
    struct RequiresExpression;
    struct QualifiedNameExpression;
    struct PathExpression;
    struct ReadExpression;
    struct SyntaxTreeExpression;
    struct ProductValueTypeExpression;
    struct SubobjectValueExpression;
    struct PackedTemplateArguments;
    struct StringLiteral;
}
