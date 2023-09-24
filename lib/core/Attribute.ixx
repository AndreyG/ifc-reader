export module ifc:Attribute;

import :ExprIndex;

import ifc.AbstractReference;
import ifc.common_types;
import ifc.Word;

#include "partition_defines.h"

export namespace ifc
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

    using AttrIndex = AbstractReference<4, AttrSort>;

    struct AttrBasic
    {
        Word word;

        PARTITION_NAME("attr.basic");
        PARTITION_SORT(AttrSort::Basic);
    };

    struct AttrScoped
    {
        Word scope;
        Word member;

        PARTITION_NAME("attr.scoped");
        PARTITION_SORT(AttrSort::Scoped);
    };

    struct AttrLabeled
    {
        Word label;
        AttrIndex attribute;

        PARTITION_NAME("attr.labeled");
        PARTITION_SORT(AttrSort::Labeled);
    };

    struct AttrCalled
    {
        AttrIndex function;
        AttrIndex arguments;

        PARTITION_NAME("attr.called");
        PARTITION_SORT(AttrSort::Called);
    };

    struct AttrExpanded
    {
        AttrIndex operand;

        PARTITION_NAME("attr.expanded");
        PARTITION_SORT(AttrSort::Expanded);
    };

    struct AttrFactored
    {
        Word factor;
        AttrIndex terms;

        PARTITION_NAME("attr.factored");
        PARTITION_SORT(AttrSort::Factored);
    };

    struct AttrElaborated
    {
        ExprIndex expression;

        PARTITION_NAME("attr.elaborated");
        PARTITION_SORT(AttrSort::Elaborated);
    };

    struct AttrTuple
    {
        Index start;
        Cardinality cardinality;

        PARTITION_NAME("attr.tuple");
        PARTITION_SORT(AttrSort::Tuple);
    };
}
