module;

#include <compare>

export module reflifc:Word;

import ifc;
import ifc.Word;

namespace reflifc
{
    export struct Word
    {
        Word(ifc::File const* ifc, ifc::Word const& word)
            : ifc_(ifc)
            , word_(&word)
        {
        }

        bool        is_identifier() const { return word_->sort == ifc::WordSort::Identifier; }
        char const* as_identifier() const { return ifc_->get_string(static_cast<ifc::TextOffset>(word_->index)); }

        auto operator<=>(Word const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Word const* word_;
    };
}
