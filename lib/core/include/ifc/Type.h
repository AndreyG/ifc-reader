#pragma once

#include "TypeFwd.h"

#include "CallingConvention.h"
#include "DeclarationFwd.h"
#include "NoexceptSpecification.h"
#include "SyntaxTreeFwd.h"

namespace ifc
{
    enum class TypeSort
    {
        VendorExtension = 0x00,
        Fundamental     = 0x01,
        Designated      = 0x02,
        Tor             = 0x03,
        Syntactic       = 0x04,
        Expansion       = 0x05,
        Pointer         = 0x06,
        PointerToMember = 0x07,
        LvalueReference = 0x08,
        RvalueReference = 0x09,
        Function        = 0x0A,
        Method          = 0x0B,
        Typename        = 0x0D,
        Base            = 0x0F,
        Decltype        = 0x10,
        Placeholder     = 0x11,
        Qualified       = 0x0E,
        Tuple           = 0x12,
        Forall          = 0x13,
        Unaligned       = 0x14,
        SyntaxTree      = 0x15,
    };

    enum class TypeBasis : uint8_t
    {
        Void,
        Bool,
        Char,
        Wchar_t,
        Int,
        Float,
        Double,
        Nullptr,
        Ellipsis,
        SegmentType,
        Class,
        Struct,
        Union,
        Enum,
        Typename,
        Namespace,
        Interface,
        Function,
        Empty,
        VariableTemplate,
        Concept,
        Auto,
        DecltypeAuto,
        Overload
    };

    enum class TypePrecision : uint8_t
    {
        Default,
        Short,
        Long,
        Bit8,
        Bit16,
        Bit32,
        Bit64,
        Bit128,
    };

    enum class TypeSign : uint8_t
    {
        Plain,
        Signed,
        Unsigned,
    };

    struct FundamentalType
    {
        TypeBasis basis;
        TypePrecision precision;
        TypeSign sign;
        uint8_t _padding_;

        PARTITION_NAME("type.fundamental");
    };

    struct DesignatedType
    {
        DeclIndex decl;

        PARTITION_NAME("type.designated");
    };

    struct SyntacticType
    {
        ExprIndex expr;

        PARTITION_NAME("type.syntactic");
    };

    enum class ExpansionMode : uint8_t
    {
        Full,
        Partial
    };

    struct ExpansionType
    {
        TypeIndex pack;
        ExpansionMode mode;

        PARTITION_NAME("type.expansion");
    };

    struct PointerType
    {
        TypeIndex pointee;

        PARTITION_NAME("type.pointer");
    };

    enum class FunctionTypeTraits : uint8_t
    {
        None        = 0,
        Const       = 1 << 0,
        Volatile    = 1 << 1,
        Lvalue      = 1 << 2,
        Rvalue      = 1 << 3,
    };

    inline bool has_trait(FunctionTypeTraits a, FunctionTypeTraits b)
    {
        return (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;
    }

    struct FunctionType
    {
        TypeIndex target;
        TypeIndex source;
        NoexceptSpecification eh_spec;
        CallingConvention convention;
        FunctionTypeTraits traits;

        PARTITION_NAME("type.function");
    };

    struct MethodType
    {
        TypeIndex target;
        TypeIndex source;
        TypeIndex scope;
        NoexceptSpecification eh_spec;
        CallingConvention convention;
        FunctionTypeTraits traits;

        PARTITION_NAME("type.nonstatic-member-function");
    };

    struct TorType
    {
        TypeIndex source;
        NoexceptSpecification eh_spec;
        CallingConvention convention;

        PARTITION_NAME("type.tor");
    };

    struct BaseType
    {
        TypeIndex type;
        Access access;

        enum Specifiers : uint8_t
        {
            Shared   = 1 << 0,
            Expanded = 1 << 1,
        };

        Specifiers specifiers;

        PARTITION_NAME("type.base");
    };

    struct TupleType : Sequence
    {
        PARTITION_NAME("type.tuple");
    };

    struct LvalueReference
    {
        TypeIndex referee;

        PARTITION_NAME("type.lvalue-reference");
    };

    struct RvalueReference
    {
        TypeIndex referee;

        PARTITION_NAME("type.rvalue-reference");
    };

    enum class Qualifiers : uint8_t
    {
        None        = 0,
        Const       = 1 << 0,
        Volatile    = 1 << 1,
        Restrict    = 1 << 2,
    };

    inline bool has_qualifier(Qualifiers a, Qualifiers b)
    {
        return (static_cast<uint8_t>(a) & static_cast<uint8_t>(b)) != 0;
    }

    struct QualifiedType
    {
        TypeIndex unqualified;
        Qualifiers qualifiers;

        PARTITION_NAME("type.qualified");
    };

    struct ForallType
    {
        ChartIndex chart;
        TypeIndex subject;

        PARTITION_NAME("type.forall");
    };

    struct SyntaxType
    {
        SyntaxIndex syntax;

        PARTITION_NAME("type.syntax-tree");
    };

    struct PlaceholderType
    {
        ExprIndex constraint;
        TypeBasis basis;
        TypeIndex elaboration;

        PARTITION_NAME("type.placeholder");
    };

    struct TypenameType
    {
        ExprIndex path;

        PARTITION_NAME("type.typename");
    };
}
