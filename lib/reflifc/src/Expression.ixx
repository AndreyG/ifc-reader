module;

#include <compare>

export module reflifc:Expression;

import reflifc.Literal;
import reflifc.StringLiteral;
import ifc;

namespace reflifc
{
    struct MonadExpression;
    struct DyadExpression;
    struct CallExpression;
    struct SizeofExpression;
    struct AlignofExpression;
    struct PathExpression;
    struct ProductValueTypeExpression;
    struct ReadExpression;
    struct RequiresExpression;
    struct UnqualifiedIdExpression;
    struct QualifiedNameExpression;

    struct Declaration;
    struct Syntax;
    struct Type;
    struct TemplateId;
    struct TemplateReference;

    export struct Expression
    {
        Expression(ifc::File const* ifc, ifc::ExprIndex index)
            : ifc_(ifc)
            , index_(index)
        {
        }

        explicit operator bool() const
        {
            return !index_.is_null();
        }

        bool            is_monad() const;
        MonadExpression as_monad() const;

        bool            is_dyad() const;
        DyadExpression  as_dyad() const;

        bool                    is_unqualified_id() const;
        UnqualifiedIdExpression as_unqualified_id() const;

        bool                    is_qualified_name() const;
        QualifiedNameExpression as_qualified_name() const;

        bool            is_call() const;
        CallExpression  as_call() const;

        bool            is_literal() const;
        Literal         as_literal() const;

        bool            is_string_literal() const;
        StringLiteral   as_string_literal() const;

        bool            is_type() const;
        Type            as_type() const;

        bool            is_read() const;
        ReadExpression  as_read() const;

        bool            is_template_id() const;
        TemplateId      as_template_id() const;

        bool                is_template_reference() const;
        TemplateReference   as_template_reference() const;

        bool            is_path() const;
        PathExpression  as_path() const;

        bool            is_qualref()        const;
        Declaration     referenced_decl()   const;

        Syntax syntax() const;

        Expression      packed_template_arguments() const;

        SizeofExpression    as_sizeof()  const;
        AlignofExpression   as_alignof() const;

        bool                is_requires() const;
        RequiresExpression  as_requires() const;

        bool                       is_product_value_type() const;
        ProductValueTypeExpression as_product_value_type() const;

        ifc::ExprSort sort() const { return index_.sort(); }

        std::partial_ordering operator<=>(Expression const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::ExprIndex index_;
    };
}
