#include "ifc/accessors.h"

namespace ifc
{
    namespace
    {
        void get_namespaces_recursively(File const& file, ScopeDescriptor scope, std::vector<ScopeDescriptor> & out)
        {
            out.push_back(scope);
            for (Declaration decl : get_declarations(file, scope))
            {
                if (decl.index.sort() != DeclSort::Scope)
                    continue;

                ScopeDeclaration const & scope_decl = get_scope(file, decl.index);
                if (get_kind(scope_decl, file) != TypeBasis::Namespace)
                    continue;

                get_namespaces_recursively(file, get_descriptor(scope_decl, file), out);
            }
        }
    }

    std::vector<ScopeDescriptor> get_namespaces_recursively(File const& file)
    {
        std::vector<ScopeDescriptor> result;
        get_namespaces_recursively(file, file.global_scope(), result);
        return result;
    }

    bool is_class(ScopeDeclaration const& scope, File const& file)
    {
        switch (get_kind(scope, file))
        {
        case TypeBasis::Class:
        case TypeBasis::Struct:
            return true;
        default:
            return false;
        }
    }

    ScopeDescriptor get_descriptor(ScopeDeclaration const& ns, File const& file)
    {
        return file.scope_descriptors()[ns.initializer];
    }
}
