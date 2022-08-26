#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class SyntaxSort;
    using SyntaxIndex = AbstractReference<7, SyntaxSort>;

    struct SimpleTypeSpecifier;
    struct TypeSpecifierSeq;
    struct DeclSpecifierSeq;
    struct TypeIdSyntax;
    struct DeclaratorSyntax;
    struct PointerDeclaratorSyntax;
    struct FunctionDeclaratorSyntax;
    struct ParameterDeclaratorSyntax;
    struct ExpressionSyntax;
    struct SimpleRequirementSyntax;
    struct TypeRequirementSyntax;
    struct CompoundRequirementSyntax;
    struct NestedRequirementSyntax;
    struct RequirementBodySyntax;
    struct TypeTemplateArgumentSyntax;
    struct TemplateArgumentListSyntax;
    struct TemplateIdSyntax;
    struct TypeTraitIntrinsicSyntax;
    struct TupleSyntax;
}
