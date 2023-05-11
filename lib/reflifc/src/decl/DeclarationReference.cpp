#include "reflifc/decl/DeclarationReference.h".

#include "ifc/File.h"
#include "ifc/Declaration.h"

namespace reflifc
{
	const char* DeclarationReference::owner() const
	{
		return ifc_->get_string(decl_reference_->unit.owner);
	}

	const char* DeclarationReference::partition() const
	{
		return ifc_->get_string(decl_reference_->unit.partition);
	}

	ifc::DeclIndex DeclarationReference::local_index() const
	{
		return decl_reference_->local_index;
	}

	reflifc::Declaration DeclarationReference::referenced_declaration(ifc::Environment& environment) const
	{
		const auto& other_ifc = environment.get_referenced_module(decl_reference_->unit, *ifc_);
		return reflifc::Declaration(&other_ifc, decl_reference_->local_index);
	}
}