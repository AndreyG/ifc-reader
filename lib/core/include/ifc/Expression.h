#pragma once

#include "ExpressionFwd.h"
#include "DeclarationFwd.h"
#include "NameFwd.h"
#include "TypeFwd.h"
#include "SyntaxTreeFwd.h"

#include "Literal.h"
#include "SourceLocation.h"
#include "Operator.h"

#include "common_types.h"

namespace ifc
{
    enum class ExprSort
    {
        VendorExtension     = 0x00,
        Empty               = 0x01,
        Literal             = 0x02,
        Lambda              = 0x03,
        Type                = 0x04,
        NamedDecl           = 0x05,
        UnresolvedId        = 0x06,
        TemplateId          = 0x07,
        UnqualifiedId       = 0x08,
        SimpleIdentifier    = 0x09,
        Pointer             = 0x0A,
        QualifiedName       = 0x0B,
        Path                = 0x0C,
        Read                = 0x0D,
        Monad               = 0x0E,
        Dyad                = 0x0F,
        Triad               = 0x10,
        String              = 0x11,
        Temporary           = 0x12,
        Call                = 0x13,
        MemberInitializer   = 0x14,
        MemberAccess        = 0x15,
        InheritancePath     = 0x16,
        InitializerList     = 0x17,
        Cast                = 0x18,
        Condition           = 0x19,
        ExpressionList      = 0x1A,
        SizeofType          = 0x1B,
        Alignof             = 0x1C,
        New                 = 0x1D,
        Delete              = 0x1E,
        Typeid              = 0x1F,
        DestructorCall      = 0x20,
        SyntaxTree          = 0x21,
        FunctionString      = 0x22,
        CompoundString      = 0x23,
        StringSequence      = 0x24,
        Initializer         = 0x25,
        Requires            = 0x26,
        UnaryFold           = 0x27,
        BinaryFold          = 0x28,
        HierarchyConversion = 0x29,
        ProductTypeValue    = 0x2A,
        SumTypeValue        = 0x2B,
        SubobjectValue      = 0x2C,
        ArrayValue          = 0x2D,
        DynamicDispatch     = 0x2E,
        VirtualFunctionConversion
                            = 0x2F,
        Placeholder         = 0x30,
        Expansion           = 0x31,
        Generic             = 0x32,
        Tuple               = 0x33,
        Nullptr             = 0x34,
        This                = 0x35,
        TemplateReference   = 0x36,
        PushState           = 0x37,
        TypeTraitIntrinsic  = 0x38,
        DesignatedInitializer
                            = 0x39,
        PackedTemplateArguments
                            = 0x3A,
        Tokens              = 0x3B,
        AssignInitializer   = 0x3C,
    };

    enum class StringSort : uint8_t {
        Ordinary,
        UTF8,
        Char16,
        Char32,
        Wide,
    };

    struct ExpressionBase
    {
        SourceLocation source;
        TypeIndex type;
    };

    struct LiteralExpression : ExpressionBase
    {
        LitIndex value;

        PARTITION_NAME("expr.literal");
        PARTITION_SORT(ExprSort::Literal);
    };

    struct NamedDecl : ExpressionBase
    {
        DeclIndex resolution;

        PARTITION_NAME("expr.decl");
        PARTITION_SORT(ExprSort::NamedDecl);
    };

    struct UnqualifiedId : ExpressionBase
    {
        NameIndex name;
        ExprIndex resolution;
        SourceLocation template_keyword;

        PARTITION_NAME("expr.unqualified-id");
        PARTITION_SORT(ExprSort::UnqualifiedId);
    };

    struct TemplateId : ExpressionBase
    {
        ExprIndex primary;
        ExprIndex arguments;

        PARTITION_NAME("expr.template-id");
        PARTITION_SORT(ExprSort::TemplateId);
    };

    struct TemplateReference : ExpressionBase
    {
        DeclIndex member;
        NameIndex member_name;
        TypeIndex scope;
        ExprIndex arguments;

        PARTITION_NAME("expr.template-reference");
        PARTITION_SORT(ExprSort::TemplateReference);
    };

    struct TupleExpression : ExpressionBase
    {
        Sequence seq;

        PARTITION_NAME("expr.tuple");
        PARTITION_SORT(ExprSort::Tuple);
    };

    struct ExpressionListExpression
    {
        SourceLocation left, right;
        ExprIndex contents;

        enum class DelimiterSort : uint8_t
        {
            Unknown = 0,
            Brace = 1,
            Parenthesis = 2,
        } delimiter;

        PARTITION_NAME("expr.expression-list");
        PARTITION_SORT(ExprSort::ExpressionList);
    };

    struct TypeExpression : ExpressionBase
    {
        TypeIndex denotation;

        PARTITION_NAME("expr.type");
        PARTITION_SORT(ExprSort::Type);
    };

    struct PackedTemplateArguments : ExpressionBase
    {
        ExprIndex arguments;

        PARTITION_NAME("expr.packed-template-arguments");
        PARTITION_SORT(ExprSort::PackedTemplateArguments);
    };

    struct MonadExpression : ExpressionBase
    {
        DeclIndex impl;
        ExprIndex argument;
        MonadicOperator op;

        PARTITION_NAME("expr.monad");
        PARTITION_SORT(ExprSort::Monad);
    };

    struct DyadExpression : ExpressionBase
    {
        DeclIndex impl;
        ExprIndex arguments[2];
        DyadicOperator op;

        PARTITION_NAME("expr.dyad");
        PARTITION_SORT(ExprSort::Dyad);
    };

    struct StringExpression : ExpressionBase
    {
        StringIndex string_index;

        PARTITION_NAME("expr.strings");
        PARTITION_SORT(ExprSort::String);
    };

    struct CallExpression : ExpressionBase
    {
        ExprIndex operation;
        ExprIndex arguments;

        PARTITION_NAME("expr.call");
        PARTITION_SORT(ExprSort::Call);
    };

    struct SizeofExpression : ExpressionBase
    {
        TypeIndex operand;

        PARTITION_NAME("expr.sizeof-type");
        PARTITION_SORT(ExprSort::SizeofType);
    };

    struct AlignofExpression : ExpressionBase
    {
        TypeIndex operand;

        PARTITION_NAME("expr.alignof");
        PARTITION_SORT(ExprSort::Alignof);
    };

    struct RequiresExpression : ExpressionBase
    {
        SyntaxIndex parameters, body;

        PARTITION_NAME("expr.requires");
        PARTITION_SORT(ExprSort::Requires);
    };

    struct QualifiedNameExpression : ExpressionBase
    {
        ExprIndex elements;
        SourceLocation template_keyword;

        PARTITION_NAME("expr.qualified-name");
        PARTITION_SORT(ExprSort::QualifiedName);
    };

    struct PathExpression : ExpressionBase
    {
        ExprIndex scope;
        ExprIndex member;

        PARTITION_NAME("expr.path");
        PARTITION_SORT(ExprSort::Path);
    };

    enum class ReadConversionSort : uint8_t
    {
        Identity,
        Indirection,
        Dereference,
        LvalueToRvalue,
        IntegralConversion,
    };

    struct ReadExpression : ExpressionBase
    {
        ExprIndex address;
        ReadConversionSort sort;

        PARTITION_NAME("expr.read");
        PARTITION_SORT(ExprSort::Read);
    };

    struct SyntaxTreeExpression
    {
        SyntaxIndex syntax;

        PARTITION_NAME("expr.syntax-tree");
        PARTITION_SORT(ExprSort::SyntaxTree);
    };

    struct ProductValueTypeExpression : ExpressionBase
    {
        TypeIndex structure;
        ExprIndex members;
        ExprIndex base_subobjects;

        PARTITION_NAME("expr.product-type-value");
        PARTITION_SORT(ExprSort::ProductTypeValue);
    };

    struct SubobjectValueExpression
    {
        ExprIndex value;

        PARTITION_NAME("expr.class-subobject-value");
        PARTITION_SORT(ExprSort::SubobjectValue);
    };

    struct StringLiteral
    {
        TextOffset start;
        Cardinality length;
        TextOffset suffix;

        PARTITION_NAME("const.str");
    };
}
