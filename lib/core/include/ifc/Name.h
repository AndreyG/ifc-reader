#pragma once

#include "NameFwd.h"
#include "TypeFwd.h"
#include "DeclarationFwd.h"
#include "ExpressionFwd.h"

#include "Operator.h"

#include "common_types.h"

namespace ifc
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

    struct OperatorFunctionName
    {
        TextOffset encoded;
        Operator operator_;

        PARTITION_NAME("name.operator");
        PARTITION_SORT(NameSort::Operator);
    };

    struct ConversionFunctionName
	{
		TypeIndex target;
        TextOffset encoded;

		PARTITION_NAME("name.conversion");
		PARTITION_SORT(NameSort::Conversion);
	};

    struct LiteralName
    {
        TextOffset encoded;

        PARTITION_NAME("name.literal");
        PARTITION_SORT(NameSort::Literal);
    };

    struct TemplateName
    {
        NameIndex name;

        PARTITION_NAME("name.template");
        PARTITION_SORT(NameSort::Template);
    };

    struct SpecializationName
    {
        NameIndex primary;
        ExprIndex arguments;

        PARTITION_NAME("name.specialization");
        PARTITION_SORT(NameSort::Specialization);
    };

    struct SourceFileName
	{
		TextOffset path;
        TextOffset guard;

		PARTITION_NAME("name.source-file");
		PARTITION_SORT(NameSort::SourceFile);
	};

	struct DeductionGuideName
	{
		DeclIndex primary_template;

		PARTITION_NAME("name.guide");
		PARTITION_SORT(NameSort::Guide);
	};
}
