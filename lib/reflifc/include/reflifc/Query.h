#pragma once

#include "Module.h"
#include "decl/ClassOrStruct.h"
#include "decl/Namespace.h"

#include <optional>

namespace reflifc
{
#define FILTER_AND_TRANSFORM(BaseDeclaration, kind) \
              std::views::filter   (&BaseDeclaration::is_ ## kind) \
            | std::views::transform(&BaseDeclaration::as_ ## kind)

    inline ViewOf<ScopeDeclaration> auto get_scope_declarations(Scope scope)
    {
        return scope.get_declarations() | FILTER_AND_TRANSFORM(Declaration, scope);
    }

    inline ViewOf<ClassOrStruct> auto get_classes_and_structs(ViewOf<ScopeDeclaration> auto declarations)
    {
        return declarations | FILTER_AND_TRANSFORM(ScopeDeclaration, class_or_struct);
    }

    inline ViewOf<ClassOrStruct> auto get_classes_and_structs(Module module)
    {
        return get_classes_and_structs(module.scope_declarations());
    }

    inline ViewOf<ClassOrStruct> auto get_classes_and_structs(Scope scope)
    {
        return get_classes_and_structs(get_scope_declarations(scope));
    }

    inline std::optional<Namespace> find_namespace_by_name(Scope scope, std::string_view name)
    {
        auto namespaces = get_scope_declarations(scope) | FILTER_AND_TRANSFORM(ScopeDeclaration, namespace);

        const auto it = std::ranges::find_if(namespaces, [name] (Namespace ns) {
            return has_name(ns, name);
        });

        if (it == namespaces.end())
            return std::nullopt;
        return *it;
    }

#undef FILTER_AND_TRANSFORM
}
