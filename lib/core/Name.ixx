export module ifc:Name;

import :ExprIndex;
import :NameIndex;

import ifc.common_types;

#include "partition_defines.h"

export namespace ifc
{
    struct Operator
    {
    private:
        uint16_t tag    : 4;
        uint16_t index  : 12;

    public:
        enum class Sort
        {
            Niladic = 0x00,
            Monadic = 0x01,
            Dyadic  = 0x02,
            Triadic = 0x03,
            Storage = 0x0E,
            Variadic= 0x0F,
        };

        Sort sort() const
        {
            return static_cast<Sort>(tag);
        }

        template<typename E>
        E value() const
        {
            return static_cast<E>(index);
        }
    };

    static_assert(sizeof(Operator) == sizeof(uint16_t));

    enum class VariadicOperatorSort
    {
        MsvcIsConstructible = 0x402,
        // TODO
    };

    struct OperatorFunctionName
    {
        TextOffset encoded;
        Operator operator_;

        PARTITION_NAME("name.operator");
        PARTITION_SORT(NameSort::Operator);
    };

    struct SpecializationName
    {
        NameIndex primary;
        ExprIndex arguments;

        PARTITION_NAME("name.specialization");
        PARTITION_SORT(NameSort::Specialization);
    };

    struct LiteralName
    {
        TextOffset encoded;

        PARTITION_NAME("name.literal");
        PARTITION_SORT(NameSort::Literal);
    };
}
