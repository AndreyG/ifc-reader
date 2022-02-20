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

        static constexpr std::string_view PartitionName = "attr.basic";
    };

    struct AttrScoped
    {
        Word scope;
        Word member;

        static constexpr std::string_view PartitionName = "attr.scoped";
    };

    struct AttrLabeled
    {
        Word label;
        AttrIndex attribute;

        static constexpr std::string_view PartitionName = "attr.labeled";
    };

    struct AttrCalled
    {
        AttrIndex function;
        AttrIndex arguments;

        static constexpr std::string_view PartitionName = "attr.called";
    };

    struct AttrExpanded
    {
        AttrIndex operand;

        static constexpr std::string_view PartitionName = "attr.expanded";
    };

    struct AttrFactored
    {
        Word factor;
        AttrIndex terms;

        static constexpr std::string_view PartitionName = "attr.factored";
    };

    struct AttrElaborated
    {
        ExprIndex expression;

        static constexpr std::string_view PartitionName = "attr.elaborated";
    };

    struct AttrTuple
    {
        Index start;
        Cardinality cardinality;

        static constexpr std::string_view PartitionName = "attr.tuple";
    };
}
