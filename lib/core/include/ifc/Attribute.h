#pragma once

#include "AttributeFwd.h"
#include "ExpressionFwd.h"

#include "common_types.h"

#include "Word.h"

namespace ifc
{
    enum class AttrSort
    {
        Nothing    = 0x00,
        Basic      = 0x01,
        Scoped     = 0x02,
        Labeled    = 0x03,
        Called     = 0x04,
        Expanded   = 0x05,
        Factored   = 0x06,
        Elaborated = 0x07,
        Tuple      = 0x08,
    };

    struct AttrBasic
    {
        Word word;

        PARTITION_NAME("attr.basic");
    };

    struct AttrScoped
    {
        Word scope;
        Word member;

        PARTITION_NAME("attr.scoped");
    };

    struct AttrLabeled
    {
        Word label;
        AttrIndex attribute;

        PARTITION_NAME("attr.labeled");
    };

    struct AttrCalled
    {
        AttrIndex function;
        AttrIndex arguments;

        PARTITION_NAME("attr.called");
    };

    struct AttrExpanded
    {
        AttrIndex operand;

        PARTITION_NAME("attr.expanded");
    };

    struct AttrFactored
    {
        Word factor;
        AttrIndex terms;

        PARTITION_NAME("attr.factored");
    };

    struct AttrElaborated
    {
        ExprIndex expression;

        PARTITION_NAME("attr.elaborated");
    };

    struct AttrTuple
    {
        Index start;
        Cardinality cardinality;

        PARTITION_NAME("attr.tuple");
    };
}
