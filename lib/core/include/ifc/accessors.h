#pragma once

#include "Declaration.h"
#include "File.h"
#include "Type.h"

#include <cassert>
#include <functional>
#include <vector>

namespace ifc
{
    std::vector<ScopeDescriptor> get_namespaces_recursively(File const &);

    bool is_class(ScopeDeclaration const &, File const &);

    ScopeDescriptor get_descriptor(ScopeDeclaration const &, File const &);

    inline std::ranges::view auto get_classes(File const & file, ScopeDescriptor ns)
    {
        using namespace std::views;
        using namespace std::placeholders;

        auto all_declarations = get_declarations(file, ns);
        auto file_cref = std::cref(file);

        return all_declarations
            | transform(&Declaration::index)
            | filter([] (DeclIndex decl) { return decl.sort() == DeclSort::Scope; })
            | transform(std::bind(get_scope, file_cref, _1))
            | filter(std::bind(is_class, _1, file_cref))
            ;
    }

    inline std::ranges::view auto get_methods(File const & file, ScopeDeclaration const & klass)
    {
        assert(is_class(klass, file));

        const auto scope_index = klass.initializer;
        if (is_null(scope_index))
            throw std::logic_error("class is incomplete");

        using namespace std::views;

        auto all_members = get_declarations(file, file.scope_descriptors()[scope_index]);
        auto methods = file.methods();
        return all_members
            | filter([] (Declaration decl) { return decl.index.sort() == DeclSort::Method; })
            | transform([methods] (Declaration decl) -> MethodDeclaration const & { return methods[decl.index]; })
            ;
    }
}
