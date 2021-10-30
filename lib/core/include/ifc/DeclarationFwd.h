#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class DeclSort;
    using DeclIndex = AbstractReference<5, DeclSort>;

    struct Declaration;
    struct DeclReference;
    struct VariableDeclaration;
    struct ParameterDeclaration;
    struct ScopeDeclaration;
    struct FunctionDeclaration;
    struct MethodDeclaration;
    struct Constructor;
    struct Destructor;
    struct AliasDeclaration;
    struct Enumeration;
    struct UsingDeclaration;
    struct TemplateDeclaration;
}
