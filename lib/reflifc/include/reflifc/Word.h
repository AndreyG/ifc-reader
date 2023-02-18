#pragma once

#include <ifc/FileFwd.h>
#include <ifc/WordFwd.h>

namespace reflifc
{
    struct Word
    {
        Word(ifc::File const& ifc, ifc::Word const& word)
            : ifc_(ifc)
            , word_(word)
        {
        }

        bool        is_identifier() const;
        char const* as_identifier() const;

    private:
        ifc::File const& ifc_;
        ifc::Word const& word_;
    };
}
