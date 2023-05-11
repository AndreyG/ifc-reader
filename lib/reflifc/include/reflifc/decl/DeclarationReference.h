#pragma once

#include "reflifc/Declaration.h"

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

        const char* owner() const;
        const char* partition() const;
        ifc::DeclIndex local_index() const;
        reflifc::Declaration referenced_declaration(ifc::Environment& environment) const;

    private:
        ifc::File const* ifc_;
        ifc::DeclReference const* decl_reference_;
	};
}