module;

#include <compare>

export module reflifc:DeclarationReference;

import :Declaration;
import :Module;

import ifc;
import ifc.Environment;

namespace reflifc
{
	export struct DeclarationReference
	{
        DeclarationReference(ifc::File const* ifc, ifc::DeclReference const& decl_reference)
            : ifc_(ifc)
            , decl_reference_(&decl_reference)
        {
        }
        
        ModuleReference module_reference() const
        {
        	return ModuleReference(ifc_, decl_reference_->unit);
        }

        Declaration referenced_declaration(ifc::Environment& environment) const
        {
        	const auto& other_ifc = environment.get_referenced_module(decl_reference_->unit, *ifc_);
        	return Declaration(&other_ifc, decl_reference_->local_index);
        }        

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(DeclarationReference const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::DeclReference const* decl_reference_;
	};
}
