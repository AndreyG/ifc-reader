#pragma once

#include <cstdint>

namespace ifc
{
    enum class WordSort;

    struct Sentence;
    struct Word;

    enum class SourceDirective : uint16_t;
    enum class SourcePunctuator : uint16_t;
    enum class SourceLiteral : uint16_t;
    enum class SourceOperator : uint16_t;
    enum class SourceKeyword : uint16_t;
    enum class SourceIdentifier : uint16_t;

}