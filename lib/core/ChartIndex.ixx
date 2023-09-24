export module ifc:ChartIndex;

import ifc.AbstractReference;

export namespace ifc
{
	enum class ChartSort
	{
		None        = 0x00,
		Unilevel    = 0x01,
		Multilevel  = 0x02,
	};

	using ChartIndex = AbstractReference<2, ChartSort>;
}
