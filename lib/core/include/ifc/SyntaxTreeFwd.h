#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class SyntaxSort;
    using SyntaxIndex = AbstractReference<7, SyntaxSort>;

    struct SimpleTypeSpecifier;
    struct TypeSpecifierSeq;
    struct TypeIdSyntax;
    struct DeclaratorSyntax;
    struct PointerDeclaratorSyntax;
    struct FunctionDeclaratorSyntax;
    struct ParameterDeclaratorSyntax;
    struct ExpressionSyntax;
    struct TypeTemplateArgumentSyntax;
    struct TemplateArgumentListSyntax;
    struct TemplateIdSyntax;
    struct TupleSyntax;
}
