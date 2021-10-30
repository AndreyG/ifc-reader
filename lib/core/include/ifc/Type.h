#pragma once

#include "TypeFwd.h"

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
        Qualified       = 0x0E,
        Tuple           = 0x12,
        Forall          = 0x13,
        // TODO
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
        Auto,
        DecltypeAuto,
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

        static constexpr std::string_view PartitionName = "type.fundamental";
    };

    struct DesignatedType
    {
        DeclIndex decl;

        static constexpr std::string_view PartitionName = "type.designated";
    };

    struct SyntacticType
    {
        ExprIndex expr;

        static constexpr std::string_view PartitionName = "type.syntactic";
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

        static constexpr std::string_view PartitionName = "type.expansion";
    };

    struct PointerType
    {
        TypeIndex pointee;

        static constexpr std::string_view PartitionName = "type.pointer";
    };

    enum class CallingConvention : uint8_t
    {
        Cdecl,
        Fast,
        Std,
        This,
        Clr,
        Vector,
        Eabi,
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

    enum class NoexceptSort : uint8_t
    {
        None,
        False,
        True,
        Expression,
        Inferred,
        Unenforced,
    };

    struct NoexceptSpecification
    {
        SentenceIndex words;
        NoexceptSort sort;
    };

    struct FunctionType
    {
        TypeIndex target;
        TypeIndex source;
        NoexceptSpecification eh_spec;
        CallingConvention convention;
        FunctionTypeTraits traits;

        static constexpr std::string_view PartitionName = "type.function";
    };

    struct MethodType
    {
        TypeIndex target;
        TypeIndex source;
        TypeIndex scope;
        NoexceptSpecification eh_spec;
        CallingConvention convention;
        FunctionTypeTraits traits;

        static constexpr std::string_view PartitionName = "type.nonstatic-member-function";
    };

    struct TupleType : Sequence
    {
        static constexpr std::string_view PartitionName = "type.tuple";
    };

    struct LvalueReference
    {
        TypeIndex referee;

        static constexpr std::string_view PartitionName = "type.lvalue-reference";
    };

    struct RvalueReference
    {
        TypeIndex referee;

        static constexpr std::string_view PartitionName = "type.rvalue-reference";
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

        static constexpr std::string_view PartitionName = "type.qualified";
    };

    struct ForallType
    {
        ChartIndex chart;
        TypeIndex subject;

        static constexpr std::string_view PartitionName = "type.forall";
    };
}
