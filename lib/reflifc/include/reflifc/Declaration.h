#pragma once

#include "Attribute.h"
#include "Expression.h"
#include "ViewOf.h"
#include "HashCombine.h"

#include <ifc/File.h>
#include <ifc/Declaration.h>

namespace reflifc
{
    struct AliasDeclaration;
    struct ScopeDeclaration;
    struct ClassOrStruct;
    struct DeclarationReference;
    struct Function;
    struct Method;
    struct Constructor;
    struct Destructor;
    struct Enumeration;
    struct TemplateDeclaration;
    struct PartialSpecialization;
    struct Specialization;
    struct UsingDeclaration;
    struct Variable;
    struct Field;
    struct Parameter;
    struct Concept;
    struct IntrinsicDeclaration;

    struct Declaration
    {
        Declaration(ifc::File const* ifc, ifc::DeclIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        explicit operator bool() const
        {
            return !index_.is_null();
        }

        bool                is_scope() const;
        ScopeDeclaration    as_scope() const;

        bool                is_class_or_struct() const;
        ClassOrStruct       as_class_or_struct() const;

        bool                is_enumeration() const;
        Enumeration         as_enumeration() const;

        bool                is_alias() const;
        AliasDeclaration    as_alias() const;

        bool                is_using() const;
        UsingDeclaration    as_using() const;

        bool                is_template() const;
        TemplateDeclaration as_template() const;

        bool                is_specialization() const;
        Specialization      as_specialization() const;

        bool                    is_partial_specialization() const;
        PartialSpecialization   as_partial_specialization() const;

        bool                is_concept() const;
        Concept             as_concept() const;

        bool                is_variable() const;
        Variable            as_variable() const;

        bool                is_field() const;
        Field               as_field() const;

        bool                is_parameter() const;
        Parameter           as_parameter() const;

        bool                is_function() const;
        Function            as_function() const;

        bool                is_method() const;
        Method              as_method() const;

        bool                is_constructor() const;
        Constructor         as_constructor() const;

        bool                is_destructor() const;
        Destructor          as_destructor() const;

        bool                 is_intrinsic() const;
        IntrinsicDeclaration as_intrinsic() const;

        bool                 is_reference() const;
        DeclarationReference as_reference() const;

        ViewOf<Attribute> auto attributes() const
        {
            return ifc_->trait_declaration_attributes(index_)
                | std::views::transform([ifc = ifc_] (ifc::AttrIndex attr) { return Attribute(ifc, attr); });
        }

        ViewOf<Expression> auto friends() const
        {
            return ifc_->declarations().slice(ifc_->trait_friendship_of_class(index_))
                | std::views::transform([ifc = ifc_] (ifc::Declaration decl) {
                      return Expression(ifc, ifc->friends()[decl.index].entity);
                  });
        }

        ifc::DeclSort sort() const { return index_.sort(); }
        ifc::DeclIndex index() const { return index_; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(Declaration const& other) const = default;

    private:
        friend std::hash<Declaration>;

        ifc::File const* ifc_;
        ifc::DeclIndex index_;
    };
}

template<>
struct std::hash<reflifc::Declaration>
{
    size_t operator()(reflifc::Declaration decl) const noexcept
    {
        return reflifc::hash_combine(0, decl.ifc_, decl.index_);
    }
};
