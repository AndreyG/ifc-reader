#include "reflifc/Type.h"

#include "reflifc/Declaration.h"
#include "reflifc/Expression.h"
#include "reflifc/TemplateId.h"
#include "reflifc/expr/Path.h"
#include "reflifc/type/Array.h"
#include "reflifc/type/Base.h"
#include "reflifc/type/Expansion.h"
#include "reflifc/type/Forall.h"
#include "reflifc/type/Pointer.h"
#include "reflifc/type/Function.h"
#include "reflifc/type/Reference.h"
#include "reflifc/type/Placeholder.h"
#include "reflifc/type/Qualified.h"

#include <ifc/File.h>
#include <ifc/Type.h>
#include <ifc/Expression.h>
#include <ifc/SyntaxTree.h>

namespace reflifc
{
    bool Type::is_fundamental() const
    {
        return sort() == ifc::TypeSort::Fundamental;
    }

    ifc::FundamentalType Type::as_fundamental() const
    {
        assert(is_fundamental());
        return ifc_->fundamental_types()[index_];
    }

    bool Type::is_array() const
    {
        return sort() == ifc::TypeSort::Array;
    }

    ArrayType Type::as_array() const
    {
        return { ifc_, ifc_->array_types()[index_] };
    }

    bool Type::is_designated() const
    {
        return sort() == ifc::TypeSort::Designated;
    }

    Declaration Type::designation() const
    {
        return { ifc_, ifc_->designated_types()[index_].decl };
    }

    bool Type::is_syntactic() const
    {
        return sort() == ifc::TypeSort::Syntactic;
    }

    Expression Type::as_syntactic() const
    {
        return Expression(ifc_, ifc_->syntactic_types()[index_].expr);
    }

    bool Type::is_base() const
    {
        return sort() == ifc::TypeSort::Base;
    }

    BaseType Type::as_base() const
    {
        return { ifc_, ifc_->base_types()[index_] };
    }

    bool Type::is_lvalue_reference() const
    {
        return sort() == ifc::TypeSort::LvalueReference;
    }

    LvalueReference Type::as_lvalue_reference() const
    {
        return { ifc_, ifc_->lvalue_references()[index_] };
    }

    bool Type::is_rvalue_reference() const
    {
        return sort() == ifc::TypeSort::RvalueReference;
    }

    RvalueReference Type::as_rvalue_reference() const
    {
        return { ifc_, ifc_->rvalue_references()[index_] };
    }

    bool Type::is_pointer() const
    {
        return sort() == ifc::TypeSort::Pointer;
    }

    PointerType Type::as_pointer() const
    {
        return { ifc_, ifc_->pointer_types()[index_] };
    }

    bool Type::is_function() const
    {
        return sort() == ifc::TypeSort::Function;
    }

    FunctionType Type::as_function() const
    {
        return { ifc_, ifc_->function_types()[index_] };
    }

    bool Type::is_method() const
    {
        return sort() == ifc::TypeSort::Method;
    }

    MethodType Type::as_method() const
    {
        return { ifc_, ifc_->method_types()[index_] };
    }

    bool Type::is_qualified() const
    {
        return sort() == ifc::TypeSort::Qualified;
    }

    QualifiedType Type::as_qualified() const
    {
        return { ifc_, ifc_->qualified_types()[index_] };
    }

    bool Type::is_expansion() const
    {
        return sort() == ifc::TypeSort::Expansion;
    }

    ExpansionType Type::as_expansion() const
    {
        return { ifc_, ifc_->expansion_types()[index_] };
    }

    bool Type::is_forall() const
    {
        return sort() == ifc::TypeSort::Forall;
    }

    ForallType Type::as_forall() const
    {
        assert(is_forall());
        return { ifc_, ifc_->forall_types()[index_] };
    }

    bool Type::is_decltype() const
    {
        return sort() == ifc::TypeSort::Decltype;
    }

    Expression Type::decltype_argument() const
    {
        return { ifc_, ifc_->decltype_specifiers()[ifc_->decltype_types()[index_].argument].argument };
    }

    bool Type::is_placeholder() const
    {
        return sort() == ifc::TypeSort::Placeholder;
    }

    PlaceholderType Type::as_placeholder() const
    {
        return { ifc_, ifc_->placeholder_types()[index_] };
    }

    bool Type::is_typename() const
    {
        return sort() == ifc::TypeSort::Typename;
    }

    PathExpression Type::typename_path() const
    {
        return Expression(ifc_, ifc_->typename_types()[index_].path).as_path();
    }
}
