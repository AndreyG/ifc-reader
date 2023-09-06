#pragma once

#include "Scope.h"
#include "Field.h"
#include "Variable.h"
#include "reflifc/type/Base.h"
#include "reflifc/TupleView.h"
#include "reflifc/Type.h"
#include "reflifc/HashCombine.h"

#include <ifc/File.h>
#include <ifc/Declaration.h>

namespace reflifc
{
    struct ClassOrStruct
    {
        ClassOrStruct(ifc::File const* ifc, ifc::ScopeDeclaration const& scope)
            : ifc_(ifc)
            , scope_(&scope)
        {
        }

        bool is_complete() const;

        Name name() const;

        ifc::TypeBasis kind() const;

        ifc::Access access() const { return scope_->access; }

        ViewOf<Declaration> auto members() const
        {
            assert(is_complete());
            return Scope(ifc_, scope_->initializer).get_declarations();
        }

        ViewOf<BaseType> auto bases() const
        {
            return TupleTypeView(ifc_, scope_->base) | std::views::transform(&Type::as_base);
        }

        Declaration home_scope() const;

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(ClassOrStruct other) const = default;

    private:
        friend std::hash<ClassOrStruct>;

        ifc::File const* ifc_;
        ifc::ScopeDeclaration const* scope_;
    };

    inline ViewOf<Field> auto fields(ClassOrStruct strct)
    {
        return strct.members()
            | std::views::filter(&Declaration::is_field)
            | std::views::transform(&Declaration::as_field);
    }

    inline ViewOf<Variable> auto static_variables(ClassOrStruct strct)
    {
        return strct.members()
            | std::views::filter(&Declaration::is_variable)
            | std::views::transform(&Declaration::as_variable);
    }
}

template<>
struct std::hash<reflifc::ClassOrStruct>
{
    size_t operator()(reflifc::ClassOrStruct class_or_struct) const noexcept
    {
        return reflifc::hash_combine(0, class_or_struct.ifc_, class_or_struct.scope_);
    }
};
