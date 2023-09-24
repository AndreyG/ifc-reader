module;

#include <cassert>

module reflifc;

namespace reflifc
{
    bool Declaration::is_scope() const
    {
        return sort() == ifc::DeclSort::Scope;
    }

    ScopeDeclaration Declaration::as_scope() const
    {
        return { ifc_, ifc_->scope_declarations()[index_] };
    }

    bool Declaration::is_class_or_struct() const
    {
        return is_scope() && as_scope().is_class_or_struct();
    }

    ClassOrStruct Declaration::as_class_or_struct() const
    {
        return as_scope().as_class_or_struct();
    }

    bool Declaration::is_enumeration() const
    {
        return sort() == ifc::DeclSort::Enumeration;
    }

    Enumeration Declaration::as_enumeration() const
    {
        return { ifc_, ifc_->enumerations()[index_] };
    }

    bool Declaration::is_alias() const
    {
        return sort() == ifc::DeclSort::Alias;
    }

    AliasDeclaration Declaration::as_alias() const
    {
        return { ifc_, ifc_->alias_declarations()[index_] };
    }

    bool Declaration::is_using() const
    {
        return sort() == ifc::DeclSort::UsingDeclaration;
    }

    UsingDeclaration Declaration::as_using() const
    {
        return { ifc_, ifc_->using_declarations()[index_] };
    }

    bool Declaration::is_template() const
    {
        return sort() == ifc::DeclSort::Template;
    }

    TemplateDeclaration Declaration::as_template() const
    {
        return { ifc_, ifc_->template_declarations()[index_] };
    }

    bool Declaration::is_specialization() const
    {
        return sort() == ifc::DeclSort::Specialization;
    }

    Specialization Declaration::as_specialization() const
    {
        return { ifc_, ifc_->specializations()[index_] };
    }

    bool Declaration::is_partial_specialization() const
    {
        return sort() == ifc::DeclSort::PartialSpecialization;
    }

    PartialSpecialization Declaration::as_partial_specialization() const
    {
        return { ifc_, ifc_->partial_specializations()[index_] };
    }

    bool Declaration::is_concept() const
    {
        return sort() == ifc::DeclSort::Concept;
    }

    Concept Declaration::as_concept() const
    {
        return { ifc_, ifc_->concepts()[index_] };
    }

    bool Declaration::is_variable() const
    {
        return sort() == ifc::DeclSort::Variable;
    }

    Variable Declaration::as_variable() const
    {
        return { ifc_, ifc_->variables()[index_] };
    }

    bool Declaration::is_field() const
    {
        return sort() == ifc::DeclSort::Field;
    }

    Field Declaration::as_field() const
    {
        return { ifc_, ifc_->fields()[index_] };
    }

    bool Declaration::is_parameter() const
    {
        return sort() == ifc::DeclSort::Parameter;
    }

    Parameter Declaration::as_parameter() const
    {
        assert(is_parameter());
        return { ifc_, ifc_->parameters()[index_] };
    }

    bool Declaration::is_function() const
    {
        return sort() == ifc::DeclSort::Function;
    }

    Function Declaration::as_function() const
    {
        assert(is_function());
        return { ifc_, ifc_->functions()[index_] };
    }

    bool Declaration::is_method() const
    {
        return sort() == ifc::DeclSort::Method;
    }

    Method Declaration::as_method() const
    {
        return { ifc_, ifc_->methods()[index_] };
    }

    bool Declaration::is_constructor() const
    {
        return sort() == ifc::DeclSort::Constructor;
    }

    Constructor Declaration::as_constructor() const
    {
        return { ifc_, ifc_->constructors()[index_] };
    }

    bool Declaration::is_destructor() const
    {
        return sort() == ifc::DeclSort::Destructor;
    }

    Destructor Declaration::as_destructor() const
    {
        return { ifc_, ifc_->destructors()[index_] };
    }

    bool Declaration::is_intrinsic() const
    {
        return sort() == ifc::DeclSort::Intrinsic;
    }

    IntrinsicDeclaration Declaration::as_intrinsic() const
    {
        return { ifc_, ifc_->intrinsic_declarations()[index_] };
    }

    bool Declaration::is_reference() const
    {
        return sort() == ifc::DeclSort::Reference;
    }

    DeclarationReference Declaration::as_reference() const
    {
        return { ifc_, ifc_->decl_references()[index_] };
    }
}
