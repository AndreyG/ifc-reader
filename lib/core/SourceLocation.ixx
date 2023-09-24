export module ifc.SourceLocation;

import ifc.common_types;

export namespace ifc
{
    enum class LineIndex : uint32_t {};

    enum class Column : uint32_t {};

    struct SourceLocation
    {
        LineIndex   line;
        Column      column;

        bool is_null() const
        {
            return static_cast<uint32_t>(line)   == 0 &&
                   static_cast<uint32_t>(column) == 0;
        }
    };
}
