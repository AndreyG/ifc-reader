module;

#include <cassert>
#include <compare>

export module reflifc:Field;

import :Declaration;
import :Expression;
import :Type;

import ifc;

namespace reflifc
{
    export struct Field
    {
        Field(ifc::File const* ifc, ifc::FieldDeclaration const& field)
            : ifc_(ifc)
            , field_(&field)
        {
        }

        const char* name() const { return ifc_->get_string(field_->name); }
        Type        type() const { return { ifc_, field_->type }; }

        ifc::Access         access() const { return field_->access; }
        ifc::ObjectTraits   traits() const { return field_->traits; }

        Declaration home_scope() const { return { ifc_, field_->home_scope }; }

        bool has_initializer() const { return !field_->initializer.is_null(); }
        Expression initializer() const
        {
        	assert(has_initializer());
        	return { ifc_, field_->initializer };	        
        }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Field const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::FieldDeclaration const* field_;
    };
}
