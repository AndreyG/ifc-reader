#pragma once

#include <cstdint>


namespace ifc
{
    // The kind of an operator.
    enum class OperatorSort : uint16_t
    {
        Niladic = 0x00,
        Monadic = 0x01,
        Dyadic = 0x02,
        Triadic = 0x03,
        Storage = 0x0E,
        Variadic = 0x0F,
    };

    // Like an AbstractReference, but for operators types.
    struct Operator
    {
    private:
        uint16_t tag : 4;
        uint16_t index : 12;

    public:
        OperatorSort sort() const
        {
            return static_cast<OperatorSort>(tag);
        }

        template<typename E>
        E value() const
        {
            return static_cast<E>(index);
        }
    };

    static_assert(sizeof(Operator) == sizeof(uint16_t));

    // An operator accepting no arguments.
    enum class NiladicOperator : uint16_t
    {
        Unknown             = 0x00,
        Phantom             = 0x01,
        Constant            = 0x02,
        Nil                 = 0x03,
        Msvc                = 0x400,
        MsvcConstantObject  = 0x401,
        MsvcLambda          = 0x402
    };

    // An operator accepting one argument.
    enum class MonadicOperator : uint16_t
    {
        Unknown                             = 0x00,
        Plus                                = 0x01,
        Negate                              = 0x02,
        Deref                               = 0x03,
        Address                             = 0x04,
        Complement                          = 0x05,
        Not                                 = 0x06,
        PreIncrement                        = 0x07,
        PreDecrement                        = 0x08,
        PostIncrement                       = 0x09,
        PostDecrement                       = 0x0A,
        Truncate                            = 0x0B,
        Ceil                                = 0x0C,
        Floor                               = 0x0D,
        Paren                               = 0x0E,
        Brace                               = 0x0F,
        Alignas                             = 0x10,
        Alignof                             = 0x11,
        Sizeof                              = 0x12,
        Cardinality                         = 0x13,
        Typeid                              = 0x14,
        Noexcept                            = 0x15,
        Requires                            = 0x16,
        CoReturn                            = 0x17,
        Await                               = 0x18,
        Yield                               = 0x19,
        Throw                               = 0x1A,
        New                                 = 0x1B,
        Delete                              = 0x1C,
        DeleteArray                         = 0x1D,
        Expand                              = 0x1E,
        Read                                = 0x1F,
        Materialize                         = 0x20,
        PseudoDtorCall                      = 0x21,
        LookupGlobally                      = 0x22,
        Msvc                                = 0x400,
        MsvcAssume                          = 0x401,
        MsvcAlignof                         = 0x402,
        MsvcUuidof                          = 0x403,
        MsvcIsClass                         = 0x404,
        MsvcIsUnion                         = 0x405,
        MsvcIsEnum                          = 0x406,
        MsvcIsPolymorphic                   = 0x407,
        MsvcIsEmpty                         = 0x408,
        MsvcIsTriviallyCopyConstructible    = 0x409,
        MsvcIsTriviallyCopyAssignable       = 0x40A,
        MsvcIsTriviallyDestructible         = 0x40B,
        MsvcHasVirtualDestructor            = 0x40C,
        MsvcIsNothrowCopyConstructible      = 0x40D,
        MsvcIsNothrowCopyAssignable         = 0x40E,
        MsvcIsPod                           = 0x40F,
        MsvcIsAbstract                      = 0x410,
        MsvcIsTrivial                       = 0x411,
        MsvcIsTriviallyCopyable             = 0x412,
        MsvcIsStandardLayout                = 0x413,
        MsvcIsLiteralType                   = 0x414,
        MsvcIsTriviallyMoveConstructible    = 0x415,
        MsvcHasTrivialMoveAssign            = 0x416,
        MsvcIsTriviallyMoveAssignable       = 0x417,
        MsvcIsNothrowMoveAssignable         = 0x418,
        MsvcUnderlyingType                  = 0x419,
        MsvcIsDestructible                  = 0x41A,
        MsvcIsNothrowDestructible           = 0x41B,
        MsvcHasUniqueObjectRepresentations  = 0x41C,
        MsvcIsAggregate                     = 0x41D,
        MsvcBuiltinAddressOf                = 0x41E,
        MsvcIsRefClass                      = 0x41F,
        MsvcIsValueClass                    = 0x420,
        MsvcIsSimpleValueClass              = 0x421,
        MsvcIsInterfaceClass                = 0x422,
        MsvcIsDelegate                      = 0x423,
        MsvcIsFinal                         = 0x424,
        MsvcIsSealed                        = 0x425,
        MsvcHasFinalizer                    = 0x426,
        MsvcHasCopy                         = 0x427,
        MsvcHasAssign                       = 0x428,
        MsvcHasUserDestructor               = 0x429,
        MsvcConfusion                       = 0xFE0,
        MsvcConfusedExpand                  = 0xFE1,
        MsvcConfusedDependentSizeof         = 0xFE2,
        MsvcConfusedPopState                = 0xFE3,
        MsvcConfusedDtorAction              = 0xFE4,
        MsvcConfusedVtorDisplacement        = 0xFE5,
        MsvcConfusedDependentExpression     = 0xFE6,
        MsvcConfusedSubstitution            = 0xFE7,
        MsvcConfusedAggregateReturn         = 0xFE8
    };

    // An operator accepting two arguments.
    enum class DyadicOperator : uint16_t
    {
        Unknown                                         = 0x00,
        Plus                                            = 0x01,
        Minus                                           = 0x02,
        Mult                                            = 0x03,
        Slash                                           = 0x04,
        Modulo                                          = 0x05,
        Remainder                                       = 0x06,
        Bitand                                          = 0x07,
        Bitor                                           = 0x08,
        Bitxor                                          = 0x09,
        Lshift                                          = 0x0A,
        Rshift                                          = 0x0B,
        Equal                                           = 0x0C,
        NotEqual                                        = 0x0D,
        Less                                            = 0x0E,
        LessEqual                                       = 0x0F,
        Greater                                         = 0x10,
        GreaterEqual                                    = 0x11,
        Compare                                         = 0x12,
        LogicAnd                                        = 0x13,
        LogicOr                                         = 0x14,
        Assign                                          = 0x15,
        PlusAssign                                      = 0x16,
        MinusAssign                                     = 0x17,
        MultAssign                                      = 0x18,
        SlashAssign                                     = 0x19,
        ModuloAssign                                    = 0x1A,
        BitandAssign                                    = 0x1B,
        BitorAssign                                     = 0x1C,
        BitxorAssign                                    = 0x1D,
        LshiftAssign                                    = 0x1E,
        RshiftAssign                                    = 0x1F,
        Comma                                           = 0x20,
        Dot                                             = 0x21,
        Arrow                                           = 0x22,
        DotStar                                         = 0x23,
        ArrowStar                                       = 0x24,
        Curry                                           = 0x25,
        Apply                                           = 0x26,
        Index                                           = 0x27,
        DefaultAt                                       = 0x28,
        New                                             = 0x29,
        NewArray                                        = 0x2A,
        Destruct                                        = 0x2B,
        DestructAt                                      = 0x2C,
        Cleanup                                         = 0x2D,
        Qualification                                   = 0x2E,
        Promote                                         = 0x2F,
        Demote                                          = 0x30,
        Coerce                                          = 0x31,
        Rewrite                                         = 0x32,
        Bless                                           = 0x33,
        Cast                                            = 0x34,
        ExplicitConversion                              = 0x35,
        ReinterpretCast                                 = 0x36,
        StaticCast                                      = 0x37,
        ConstCast                                       = 0x38,
        DynamicCast                                     = 0x39,
        Narrow                                          = 0x3A,
        Widen                                           = 0x3B,
        Pretend                                         = 0x3C,
        Closure                                         = 0x3D,
        ZeroInitialize                                  = 0x3E,
        ClearStorage                                    = 0x3F,
        Select                                          = 0x40,
        Msvc                                            = 0x400,
        MsvcTryCast                                     = 0x401,
        MsvcCurry                                       = 0x402,
        MsvcVirtualCurry                                = 0x403,
        MsvcAlign                                       = 0x404,
        MsvcBitSpan                                     = 0x405,
        MsvcBitfieldAccess                              = 0x406,
        MsvcObscureBitfieldAccess                       = 0x407,
        MsvcInitialize                                  = 0x408,
        MsvcBuiltinOffsetOf                             = 0x409,
        MsvcIsBaseOf                                    = 0x40A,
        MsvcIsConvertibleTo                             = 0x40B,
        MsvcIsTriviallyAssignable                       = 0x40C,
        MsvcIsNothrowAssignable                         = 0x40D,
        MsvcIsAssignable                                = 0x40E,
        MsvcIsAssignableNocheck                         = 0x40F,
        MsvcBuiltinBitCast                              = 0x410,
        MsvcBuiltinIsLayoutCompatible                   = 0x411,
        MsvcBuiltinIsPointerInterconvertibleBaseOf      = 0x412,
        MsvcBuiltinIsPointerInterconvertibleWithClass   = 0x413,
        MsvcBuiltinIsCorrespondingMember                = 0x414,
        MsvcIntrinsic                                   = 0x415,
        MsvcSaturatedArithmetic                         = 0x416,
        MsvcBuiltinAllocationAnnotation                 = 0x417
    };

    // An operator accepting three arguments.
    enum class TriadicOperator : uint16_t
    {
        Unknown                 = 0x00,
        Choice                  = 0x01,
        ConstructAt             = 0x02,
        Initialize              = 0x03,
        Msvc                    = 0x400,
        MsvcConfusion           = 0xFE0,
        MsvcConfusedPushState   = 0xFE1,
        MsvcConfusedChoice      = 0xFE2
    };

    // A storage allocation or deallocation operator.
    enum class StorageOperator : uint16_t
    {
        Unknown             = 0x00,
        AllocateSingle      = 0x01,
        AllocateArray       = 0x02,
        DeallocateSingle    = 0x03,
        DeallocateArray     = 0x04,
        MSVC                = 0x7DE
    };

    // An operator accepting any number of arguments.
    enum class VariadicOperator : uint16_t
    {
        Unknown                         = 0x00,
        Collection                      = 0x01,
        Sequence                        = 0x02,
        Msvc                            = 0x400,
        MsvcHasTrivialConstructor       = 0x401,
        MsvcIsConstructible             = 0x402,
        MsvcIsNothrowConstructible      = 0x403,
        MsvcIsTriviallyConstructible    = 0x404
    };


    inline const char* to_string(MonadicOperator op)
    {
        switch (op) {
        case MonadicOperator::Unknown:
            return "Unknown";
        case MonadicOperator::Plus:
            return "+";
        case MonadicOperator::Negate:
            return "-";
        case MonadicOperator::Deref:
            return "*";
        case MonadicOperator::Address:
            return "&";
        case MonadicOperator::Complement:
            return "~";
        case MonadicOperator::Not:
            return "!";
        case MonadicOperator::PreIncrement:
            return "(pre)++";
        case MonadicOperator::PreDecrement:
            return "(pre)--";
        case MonadicOperator::PostIncrement:
            return "(post)++";
        case MonadicOperator::PostDecrement:
            return "(post)--";
        case MonadicOperator::Truncate:
            return "(truncate)";
        case MonadicOperator::Ceil:
            return "(ceil)";
        case MonadicOperator::Floor:
            return "(floor)";
        case MonadicOperator::Paren:
            return "(paren)";
        case MonadicOperator::Brace:
            return "{brace}";
        }
        return "Unknown";
    }

    inline const char* to_string(DyadicOperator op)
    {
        switch (op) {
        case DyadicOperator::Unknown:
            return "Unknown";
        case DyadicOperator::Plus:
            return "+";
        case DyadicOperator::Minus:
            return "-";
        case DyadicOperator::Mult:
            return "*";
        case DyadicOperator::Slash:
            return "/";
        case DyadicOperator::Modulo:
            return "%";
        case DyadicOperator::Bitand:
            return "&";
        case DyadicOperator::Bitor:
            return "|";
        case DyadicOperator::Bitxor:
            return "^";
        case DyadicOperator::Lshift:
            return "<<";
        case DyadicOperator::Rshift:
            return ">>";
        case DyadicOperator::Equal:
            return "==";
        case DyadicOperator::NotEqual:
            return "!=";
        case DyadicOperator::Less:
            return "<";
        case DyadicOperator::LessEqual:
            return "<=";
        case DyadicOperator::Greater:
            return ">";
        case DyadicOperator::GreaterEqual:
            return ">=";
        case DyadicOperator::Compare:
            return "<=>";
        case DyadicOperator::LogicAnd:
            return "&&";
        case DyadicOperator::LogicOr:
            return "||";
        case DyadicOperator::Assign:
            return "=";
        case DyadicOperator::PlusAssign:
            return "+=";
        case DyadicOperator::MinusAssign:
            return "-=";
        case DyadicOperator::MultAssign:
            return "*=";
        case DyadicOperator::SlashAssign:
            return "/=";
        case DyadicOperator::ModuloAssign:
            return "%=";
        case DyadicOperator::BitandAssign:
            return "&=";
        case DyadicOperator::BitorAssign:
            return "|=";
        case DyadicOperator::BitxorAssign:
            return "^=";
        case DyadicOperator::LshiftAssign:
            return "<<=";
        case DyadicOperator::RshiftAssign:
            return ">>=";
        }
        return "Unknown";
    }
}