#include "reflifc/decl/DeclarationReference.h"

#include "ifc/File.h"
#include "ifc/Declaration.h"

namespace reflifc
{
	reflifc::ModuleReference DeclarationReference::module_reference() const
	{
		return reflifc::ModuleReference(ifc_, decl_reference_->unit);
	}

	reflifc::Declaration DeclarationReference::referenced_declaration(ifc::Environment& environment) const
	{
		const auto& other_ifc = environment.get_referenced_module(decl_reference_->unit, *ifc_);
		return reflifc::Declaration(&other_ifc, decl_reference_->local_index);
	}
}