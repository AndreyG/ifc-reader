#pragma once

#include "reflifc/Declaration.h"
#include "reflifc/Module.h"
#include "reflifc/HashCombine.h"

#include "ifc/FileFwd.h"
#include "ifc/DeclarationFwd.h"
#include "ifc/Environment.h"

namespace reflifc
{
	struct DeclarationReference
	{
        DeclarationReference(ifc::File const* ifc, ifc::DeclReference const& decl_reference)
            : ifc_(ifc)
            , decl_reference_(&decl_reference)
        {
        }
        
        reflifc::ModuleReference module_reference() const;
        reflifc::Declaration referenced_declaration(ifc::Environment& environment) const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(DeclarationReference const& other) const = default;

    private:
        friend std::hash<DeclarationReference>;

        ifc::File const* ifc_;
        ifc::DeclReference const* decl_reference_;
	};
}

template<>
struct std::hash<reflifc::DeclarationReference>
{
    size_t operator()(reflifc::DeclarationReference decl_ref) const noexcept
    {
        return reflifc::hash_combine(0, decl_ref.ifc_, decl_ref.decl_reference_);
    }
};
