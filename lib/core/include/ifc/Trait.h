#pragma once

#include "DeclarationFwd.h"

#include "common_types.h"

namespace ifc
{
	template<typename T>
	struct AssociatedTrait
	{
		DeclIndex decl;
		T trait;
	};
}