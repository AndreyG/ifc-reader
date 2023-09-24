module;

#include <cassert>
#include <ranges>

export module reflifc:TupleView;

import ifc;

namespace reflifc
{
    export template<typename Traits>
    struct TupleView : std::ranges::view_interface<TupleView<Traits>>
    {
        using Index = typename Traits::Index;
        using Sort = typename Index::Sort;
        using Element = typename Traits::Element;

        struct Iterator
        {
            using value_type = Element;
            using difference_type = std::ptrdiff_t;

            Iterator(Index const* index, ifc::File const* ifc)
                : index_(index)
                , ifc_(ifc)
            {}

            Iterator() = default;

            Element operator*() const;

            Iterator& operator++()
            {
                ++index_;
                return *this;
            }

            Iterator operator++(int)
            {
                auto res = *this;
                ++*this;
                return res;
            }

            friend bool operator==(Iterator a, Iterator b)
            {
                assert(a.ifc_ == b.ifc_);
                return a.index_ == b.index_;
            }

        private:
            Index const* index_;
            ifc::File const* ifc_;
        };

        TupleView() = default;

        TupleView(ifc::File const* ifc, Index const& index)
            : index_(&index)
            , ifc_(ifc)
        {
        }

        Iterator begin() const;
        Iterator end()   const;

        Element operator[] (size_t index) const;

        size_t size() const;
        bool   empty() const;

    private:
        ifc::Sequence get_tuple_elements() const;
        Iterator get_tuple_element(ifc::Index) const;

    private:
        Index const* index_;
        ifc::File const* ifc_;
    };

    struct Expression;
    struct Syntax;
    struct Type;

    struct TupleExpressionTraits
    {
        using Index = ifc::ExprIndex;
        using Element = Expression;
    };

    struct TupleSyntaxTraits
    {
        using Index = ifc::SyntaxIndex;
        using Element = Syntax;
    };

    struct TupleTypeTraits
    {
        using Index = ifc::TypeIndex;
        using Element = Type;
    };

    export struct TupleExpressionView : TupleView<TupleExpressionTraits>
    {
        using TupleView::TupleView;
    };

    export struct TupleSyntaxView : TupleView<TupleSyntaxTraits>
    {
        using TupleView::TupleView;
    };

    export struct TupleTypeView : TupleView<TupleTypeTraits>
    {
        using TupleView::TupleView;
    };
}
