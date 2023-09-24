export module ifc:TypeIndex;

import ifc.AbstractReference;
import ifc.common_types;

export namespace ifc
{
	enum class TypeSort
	{
		VendorExtension = 0x00,
		Fundamental     = 0x01,
		Designated      = 0x02,
		Tor             = 0x03,
		Syntactic       = 0x04,
		Expansion       = 0x05,
		Pointer         = 0x06,
		PointerToMember = 0x07,
		LvalueReference = 0x08,
		RvalueReference = 0x09,
		Function        = 0x0A,
		Method          = 0x0B,
		Array           = 0x0C,
		Typename        = 0x0D,
		Qualified       = 0x0E,
		Base            = 0x0F,
		Decltype        = 0x10,
		Placeholder     = 0x11,
		Tuple           = 0x12,
		Forall          = 0x13,
		Unaligned       = 0x14,
		SyntaxTree      = 0x15,
	};

	using TypeIndex = AbstractReference<5, TypeSort>;

    enum class Qualifiers : uint8_t;
    enum class FunctionTypeTraits : uint8_t;
}
