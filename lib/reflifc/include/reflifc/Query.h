#pragma once

#include "Module.h"
#include "decl/ClassOrStruct.h"
#include "decl/Namespace.h"

#include <optional>

namespace reflifc
{
    using namespace std::views;

    inline RangeOf<ScopeDeclaration> auto get_scope_declarations(Scope scope)
    {
        return scope.get_declarations()
            | filter(&Declaration::is_scope)
            | transform(&Declaration::as_scope);
    }

    inline RangeOf<ClassOrStruct> auto get_classes_and_structs(Module module)
    {
        return module.scope_declarations()
            | filter(&ScopeDeclaration::is_class_or_struct)
            | transform(&ScopeDeclaration::as_class_or_struct);
    }

    inline RangeOf<ClassOrStruct> auto get_classes_and_structs(Scope scope)
    {
        return get_scope_declarations(scope)
            | filter(&ScopeDeclaration::is_class_or_struct)
            | transform(&ScopeDeclaration::as_class_or_struct);
    }

    inline std::optional<Namespace> find_namespace_by_name(Scope scope, std::string_view name)
    {
        auto namespaces = get_scope_declarations(scope)
            | filter(&ScopeDeclaration::is_namespace)
            | transform(&ScopeDeclaration::as_namespace);

        const auto it = std::ranges::find_if(namespaces, [name] (Namespace ns) {
            return has_name(ns, name);
        });

        if (it == namespaces.end())
            return std::nullopt;
        return *it;
    }
}
