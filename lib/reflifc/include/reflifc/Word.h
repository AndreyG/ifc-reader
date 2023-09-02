#pragma once

#include "HashCombine.h"

#include <ifc/FileFwd.h>
#include <ifc/WordFwd.h>

namespace reflifc
{
    struct Word
    {
        Word(ifc::File const* ifc, ifc::Word const& word)
            : ifc_(ifc)
            , word_(&word)
        {
        }

        bool        is_identifier() const;
        char const* as_identifier() const;

        auto operator<=>(Word const& other) const = default;

    private:
        friend std::hash<Word>;

        ifc::File const* ifc_;
        ifc::Word const* word_;
    };
}

template<>
struct std::hash<reflifc::Word>
{
    size_t operator()(reflifc::Word const& word) const noexcept
    {
        return reflifc::hash_combine(0, word.ifc_, word.word_);
    }
};
