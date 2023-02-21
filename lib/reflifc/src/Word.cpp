#include "reflifc/Word.h"

#include <ifc/File.h>
#include <ifc/Word.h>

namespace reflifc
{
    bool Word::is_identifier() const
    {
        return word_->sort == ifc::WordSort::Identifier;
    }

    char const* Word::as_identifier() const
    {
        return ifc_->get_string(static_cast<ifc::TextOffset>(word_->index));
    }
}
