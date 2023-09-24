export module ifc:SyntaxIndex;

import ifc.AbstractReference;

export namespace ifc
{
	enum class SyntaxSort
	{
		SimpleTypeSpecifier = 0x01,
		DecltypeSpecifier   = 0x02,
		TypeSpecifierSeq    = 0x04,
		DeclSpecifierSeq    = 0x05,
		TypeId              = 0x12,
		Declarator          = 0x14,
		PointerDeclarator   = 0x15,
		FunctionDeclarator  = 0x17,
		ParameterDeclarator = 0x19,
		Expression          = 0x3A,
		RequiresClause      = 0x3E,
		SimpleRequirement   = 0x3F,
		TypeRequirement     = 0x40,
		CompoundRequirement = 0x41,
		NestedRequirement   = 0x42,
		RequirementBody     = 0x43,
		TypeTemplateArgument= 0x46,
		TemplateArgumentList= 0x49,
		TemplateId          = 0x4A,
		TypeTraitIntrinsic  = 0x63,
		Tuple               = 0x64,
		// TODO
	};

	using SyntaxIndex = AbstractReference<7, SyntaxSort>;
}
