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
    struct ExpressionSyntax;
    struct TemplateIdSyntax;
}
