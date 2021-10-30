#pragma once

#include "common_types.h"

namespace ifc
{
    enum class NoexceptSort : uint8_t
    {
        None,
        False,
        True,
        Expression,
        Inferred,
        Unenforced,
    };

    struct NoexceptSpecification
    {
        SentenceIndex words;
        NoexceptSort sort;
    };
}
