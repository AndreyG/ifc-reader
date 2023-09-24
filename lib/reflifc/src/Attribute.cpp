module;

#include <cassert>

module reflifc;

namespace reflifc
{
    Word Attribute::as_basic() const
    {
        assert(is_basic());
        return { ifc_, ifc_->basic_attributes()[index_].word };
    }

    AttributeCalled Attribute::as_called() const
    {
        assert(is_called());
        return { ifc_, ifc_->called_attributes()[index_] };
    }
}
