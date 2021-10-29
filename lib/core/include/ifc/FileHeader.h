#pragma once

#include "Scope.h"
#include "Module.h"
#include "Indices.h"

#include <array>
#include <ostream>

namespace ifc
{
    struct alignas(4) SHA256
    {
        std::array<std::byte, 256 / 8> data;
    };

    enum class Version : uint8_t {};

    inline std::ostream& operator<<(std::ostream& out, Version version)
    {
        return out << static_cast<int>(version);
    }

    enum class Abi : uint8_t {};

    enum class Architecture : uint8_t
    {
        Unknown         = 0x00, // Unknown target
        X86             = 0x01, // x86 (32-bit) target
        X64             = 0x02, // x64 (64-bit) target
        ARM32           = 0x03, // ARM (32-bit) target
        ARM64           = 0x04, // ARM (64-bit) target
        HybridX86ARM64  = 0x05, // Hybrid x86-arm64
    };

    enum class LanguageVersion : uint32_t { };

    enum class UnitSort
    {
        Source      = 0x00,
        Primary     = 0x01,
        Partition   = 0x02,
        Header      = 0x03,
        ExportedTU  = 0x04,
    };

    using UnitIndex = AbstractReference<3, UnitSort>;

    struct FileHeader
    {
        SHA256 checksum;
        Version major_version, minor_version;
        Abi abi;
        Architecture arch;
        LanguageVersion dialect;
        ByteOffset  string_table_bytes;
        Cardinality string_table_size;
        UnitIndex unit;
        TextOffset src_path;
        ScopeIndex global_scope;
        ByteOffset toc;
        Cardinality partition_count;
        bool internal;
    };
}
