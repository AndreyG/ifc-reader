module;

#include <cassert>
#include <functional>

export module reflifc:Field;

import :Declaration;
import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    struct Expression;

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
        friend std::hash<Field>;

        ifc::File const* ifc_;
        ifc::FieldDeclaration const* field_;
    };
}

template<>
struct std::hash<reflifc::Field>
{
    size_t operator()(reflifc::Field field) const noexcept
    {
        return reflifc::hash_combine(0, field.ifc_, field.field_);
    }
};
