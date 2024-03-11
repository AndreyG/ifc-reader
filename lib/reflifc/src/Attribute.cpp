#include "reflifc/Attribute.h"
#include "reflifc/Word.h"

#include <ifc/Attribute.h>
#include <ifc/File.h>

namespace reflifc
{
    bool Attribute::is_basic() const
    {
        return index_.sort() == ifc::AttrSort::Basic;
    }

    Word Attribute::as_basic() const
    {
        assert(is_basic());
        return { ifc_, ifc_->basic_attributes()[index_].word };
    }

    bool Attribute::is_called() const
    {
        return index_.sort() == ifc::AttrSort::Called;
    }

    AttributeCalled Attribute::as_called() const
    {
        assert(is_called());
        return { ifc_, ifc_->called_attributes()[index_] };
    }

    Attribute AttributeCalled::function() const
    {
        return { ifc_, attr_->function };
    }

    Attribute AttributeCalled::arguments() const
    {
        return { ifc_, attr_->arguments };
    }
}
