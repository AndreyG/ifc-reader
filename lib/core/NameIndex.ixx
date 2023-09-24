export module ifc:NameIndex;

import ifc.AbstractReference;

export namespace ifc
{
	enum class NameSort
	{
		Identifier      = 0x00,
		Operator        = 0x01,
		Conversion      = 0x02,
		Literal         = 0x03,
		Template        = 0x04,
		Specialization  = 0x05,
		SourceFile      = 0x06,
		Guide           = 0x07,
	};

	using NameIndex = AbstractReference<3, NameSort>;
}