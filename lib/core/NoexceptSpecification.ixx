export module ifc.NoexceptSpecification;

import ifc.common_types;

export namespace ifc
{
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
}
