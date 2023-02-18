#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class DeclSort : uint32_t;
    using DeclIndex = AbstractReference<5, DeclSort>;

    struct Declaration;
    struct DeclReference;
    struct VariableDeclaration;
    struct FieldDeclaration;
    struct ParameterDeclaration;
    struct ScopeDeclaration;
    struct FunctionDeclaration;
    struct MethodDeclaration;
    struct Constructor;
    struct Destructor;
    struct AliasDeclaration;
    struct Enumeration;
    struct Enumerator;
    struct UsingDeclaration;
    struct FriendDeclaration;
    struct TemplateDeclaration;
    struct Concept;
    struct IntrinsicDeclaration;

    enum class Access : uint8_t;
    enum class ObjectTraits : uint8_t;
}
