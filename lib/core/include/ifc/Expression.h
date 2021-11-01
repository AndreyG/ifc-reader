#pragma once

#include "ExpressionFwd.h"

#include "SourceLocation.h"

#include "common_types.h"

#include <string_view>

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
        xSimpleIdentifier   = 0x08,
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
        xUnaryFold          = 0x26,
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

    struct NamedDecl
    {
        SourceLocation source;
        TypeIndex type;
        DeclIndex resolution;

        static constexpr std::string_view PartitionName = "expr.decl";
    };

    struct TemplateId
    {
        SourceLocation source;
        TypeIndex type;
        ExprIndex primary;
        ExprIndex arguments;

        static constexpr std::string_view PartitionName = "expr.template-id";
    };

    struct TupleExpression
    {
        SourceLocation locus;
        TypeIndex type;
        Sequence seq;

        static constexpr std::string_view PartitionName = "expr.tuple";
    };

    struct TypeExpression
    {
        SourceLocation locus;
        TypeIndex type;
        TypeIndex denotation;

        static constexpr std::string_view PartitionName = "expr.type";
    };
}
