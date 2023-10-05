module;

#include <compare>

export module reflifc:Enumerator;

import :Expression;
import reflifc.Literal;

import ifc;

export namespace reflifc
{
    struct Enumerator
    {
        Enumerator(ifc::File const* ifc, ifc::Enumerator const& enumerator)
            : ifc_(ifc)
            , enumerator_(&enumerator)
        {
        }

        const char* name() const { return ifc_->get_string(enumerator_->name); }

        Expression value() const { return { ifc_, enumerator_->initializer }; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Enumerator const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::Enumerator const* enumerator_;
    };

    inline auto int_value(Enumerator enumerator)
    {
        return enumerator.value().as_literal().int_value();
    }
}
