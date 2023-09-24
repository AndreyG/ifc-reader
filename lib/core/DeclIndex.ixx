export module ifc:DeclIndex;

import ifc.AbstractReference;
import ifc.common_types;

export namespace ifc
{
	enum class DeclSort : uint32_t
	{
		VendorExtension         = 0x00,
		Enumerator              = 0x01,
		Variable                = 0x02,
		Parameter               = 0x03,
		Field                   = 0x04,
		Bitfield                = 0x05,
		Scope                   = 0x06,
		Enumeration             = 0x07,
		Alias                   = 0x08,
		Temploid                = 0x09,
		Template                = 0x0A,
		PartialSpecialization   = 0x0B,
		Specialization          = 0x0C,
		DefaultArgument         = 0x0D,
		Concept                 = 0x0E,
		Function                = 0x0F,
		Method                  = 0x10,
		Constructor             = 0x11,
		InheritedConstructor    = 0x12,
		Destructor              = 0x13,
		Reference               = 0x14,
		UsingDeclaration        = 0x15,
		UsingDirective          = 0x16,
		Friend                  = 0x17,
		Expansion               = 0x18,
		DeductionGuide          = 0x19,
		Barren                  = 0x1A,
		Tuple                   = 0x1B,
		SyntaxTree              = 0x1C,
		Intrinsic               = 0x1D,
		Property                = 0x1E,
		OutputSegment           = 0x1F,
	};

	using DeclIndex = AbstractReference<5, DeclSort>;

    enum class Access : uint8_t;
}
