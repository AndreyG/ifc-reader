#include "reflifc/TupleView.h"

#include "reflifc/Expression.h"
#include "reflifc/Syntax.h"
#include "reflifc/Type.h"

#include "reflifc/RangeOf.h"

#include <ifc/File.h>
#include <ifc/Expression.h>
#include <ifc/SyntaxTree.h>
#include <ifc/Type.h>

#include <string>

namespace reflifc
{
    template<typename Traits>
    typename Traits::Element TupleView<Traits>::Iterator::operator*() const
    {
        return { *ifc_, *index_ };
    }

    template<typename Traits>
    typename TupleView<Traits>::Iterator TupleView<Traits>::begin() const
    {
        if (index_->sort() == Sort::Tuple)
        {
            const auto tuple_elements = get_tuple_elements();
            return get_tuple_element(tuple_elements.start);
        }

        return { index_, ifc_ };
    }

    template<typename Traits>
    typename TupleView<Traits>::Iterator TupleView<Traits>::end() const
    {
        if (index_->is_null())
            return { index_, ifc_ };

        if (index_->sort() == Sort::Tuple)
        {
            const auto tuple_elements = get_tuple_elements();
            return get_tuple_element(tuple_elements.start + raw_count(tuple_elements.cardinality));
        }

        return { index_ + 1, ifc_ };
    }

    template<typename Traits>
    typename Traits::Element TupleView<Traits>::operator[](size_t index) const
    {
        if (index_->sort() == Sort::Tuple)
        {
            const auto tuple_elements = get_tuple_elements();
            const auto cardinality = raw_count(tuple_elements.cardinality);
            if (index >= cardinality)
                throw std::out_of_range("index (= " + std::to_string(index) + ") >= size (= " + std::to_string(cardinality) + ")");

            return *get_tuple_element(tuple_elements.start + index);
        }

        if (index_->is_null())
            throw std::out_of_range("empty TupleView");

        if (index > 0)
            throw std::out_of_range("single element TupleView");

        return { *ifc_, *index_ };
    }

    template<typename Traits>
    size_t TupleView<Traits>::size() const
    {
        if (index_->is_null())
            return 0;

        if (index_->sort() == Sort::Tuple)
            return raw_count(get_tuple_elements().cardinality);

        return 1;
    }

    template<typename Traits>
    bool TupleView<Traits>::empty() const
    {
        return index_->is_null();
    }

    template<typename> struct FuncGetter;

    template<>
    struct FuncGetter<Expression>
    {
        static constexpr auto heap = &ifc::File::expr_heap;
        static constexpr auto element = &ifc::File::tuple_expressions;
    };

    template<>
    struct FuncGetter<Type>
    {
        static constexpr auto heap = &ifc::File::type_heap;
        static constexpr auto element = &ifc::File::tuple_types;
    };

    template<>
    struct FuncGetter<Syntax>
    {
        static constexpr auto heap = &ifc::File::syntax_heap;
        static constexpr auto element = &ifc::File::tuple_syntax_trees;
    };

    template<typename Traits>
    ifc::Sequence TupleView<Traits>::get_tuple_elements() const
    {
        auto fptr = FuncGetter<Element>::element;
        return (ifc_->*fptr)()[*index_].seq;
    }

    template<typename Traits>
    typename TupleView<Traits>::Iterator TupleView<Traits>::get_tuple_element(ifc::Index index) const
    {
        auto fptr = FuncGetter<Element>::heap;
        return { &(ifc_->*fptr)()[index], ifc_ };
    }

    template struct TupleView<TupleExpressionTraits>;
    template struct TupleView<TupleSyntaxTraits>;
    template struct TupleView<TupleTypeTraits>;

    static_assert(RangeOf<TupleExpressionView,  Expression>);
    static_assert(RangeOf<TupleSyntaxView,      Syntax>);
    static_assert(RangeOf<TupleTypeView,        Type>);
}
