#pragma once

#include "AbstractReference.h"

namespace ifc
{
    enum class AttrSort;
    using AttrIndex = AbstractReference<4, AttrSort>;

    struct AttrNothing;
    struct AttrBasic;
    struct AttrScoped;
    struct AttrLabeled;
    struct AttrCalled;
    struct AttrExpanded;
    struct AttrFactored;
    struct AttrElaborated;
    struct AttrTuple;
}