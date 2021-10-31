#include "ifc/File.h"
#include "ifc/Environment.h"

#include "ifc/Chart.h"
#include "ifc/Declaration.h"
#include "ifc/Expression.h"
#include "ifc/Type.h"

#include <cassert>
#include <stdexcept>

namespace ifc
{
    using FileSignature = std::array<std::byte, 4>;

    struct File::Structure
    {
        FileSignature signature;
        FileHeader header;
    };

    File::Structure const* File::structure() const
    {
        return reinterpret_cast<Structure const *>(fmap_.data());
    }

    FileHeader const& File::header() const
    {
        return structure()->header;
    }

    const char* File::get_string(TextOffset index) const
    {
        return get_pointer<char>(header().string_table_bytes) + static_cast<size_t>(index);
    }

    ScopeDescriptor File::global_scope() const
    {
        return scope_descriptors()[header().global_scope];
    }

    ScopePartition File::scope_descriptors() const
    {
        return get_partition<ScopeDescriptor, ScopeIndex>();
    }

#define DEFINE_PARTITION_GETTER(ElementType, IndexType, Property)   \
    Partition<ElementType, IndexType> File::Property() const {      \
        if (cached_ ## Property ## _.has_value())                   \
            return *cached_ ## Property ## _;                       \
        auto result = get_partition<ElementType, IndexType>();      \
        cached_ ## Property ## _ = result;                          \
        return result;                                              \
    }

    DEFINE_PARTITION_GETTER(Declaration, Index, declarations)

#define DEFINE_DECL_PARTITION_GETTER(DeclType, DeclName) \
    DEFINE_PARTITION_GETTER(DeclType, DeclIndex, DeclName)

    DEFINE_DECL_PARTITION_GETTER(ScopeDeclaration,      scope_declarations)
    DEFINE_DECL_PARTITION_GETTER(TemplateDeclaration,   template_declarations)
    DEFINE_DECL_PARTITION_GETTER(UsingDeclaration,      using_declarations)
    DEFINE_DECL_PARTITION_GETTER(Enumeration,           enumerations)
    DEFINE_DECL_PARTITION_GETTER(AliasDeclaration,      alias_declarations)
    DEFINE_DECL_PARTITION_GETTER(DeclReference,         decl_references)
    DEFINE_DECL_PARTITION_GETTER(FunctionDeclaration,   functions)
    DEFINE_DECL_PARTITION_GETTER(MethodDeclaration,     methods)
    DEFINE_DECL_PARTITION_GETTER(Constructor,           constructors)
    DEFINE_DECL_PARTITION_GETTER(Destructor,            destructors)
    DEFINE_DECL_PARTITION_GETTER(VariableDeclaration,   variables)
    DEFINE_DECL_PARTITION_GETTER(FieldDeclaration,      fields)
    DEFINE_DECL_PARTITION_GETTER(ParameterDeclaration,  parameters)

#undef DEFINE_DECL_PARTITION_GETTER

#define DEFINE_TYPE_PARTITION_GETTER(Type, TypeName) \
    DEFINE_PARTITION_GETTER(Type, TypeIndex, TypeName)

    DEFINE_TYPE_PARTITION_GETTER(FundamentalType,    fundamental_types)
    DEFINE_TYPE_PARTITION_GETTER(DesignatedType,     designated_types)
    DEFINE_TYPE_PARTITION_GETTER(TorType,            tor_types)
    DEFINE_TYPE_PARTITION_GETTER(SyntacticType,      syntactic_types)
    DEFINE_TYPE_PARTITION_GETTER(ExpansionType,      expansion_types)
    DEFINE_TYPE_PARTITION_GETTER(PointerType,        pointer_types)
    DEFINE_TYPE_PARTITION_GETTER(FunctionType,       function_types)
    DEFINE_TYPE_PARTITION_GETTER(MethodType,         method_types)
    DEFINE_TYPE_PARTITION_GETTER(TupleType,          tuple_types)
    DEFINE_TYPE_PARTITION_GETTER(LvalueReference,    lvalue_references)
    DEFINE_TYPE_PARTITION_GETTER(RvalueReference,    rvalue_references)
    DEFINE_TYPE_PARTITION_GETTER(QualifiedType,      qualified_types)
    DEFINE_TYPE_PARTITION_GETTER(ForallType,         forall_types)

#undef DEFINE_TYPE_PARTITION_GETTER

#define DEFINE_EXPR_PARTITION_GETTER(ExprType, ExprName) \
    DEFINE_PARTITION_GETTER(ExprType, ExprIndex, ExprName)

    DEFINE_EXPR_PARTITION_GETTER(TypeExpression,    type_expressions)
    DEFINE_EXPR_PARTITION_GETTER(NamedDecl,         decl_expressions)
    DEFINE_EXPR_PARTITION_GETTER(TemplateId,        template_ids)
    DEFINE_EXPR_PARTITION_GETTER(TupleExpression,   tuple_expressions)

#undef DEFINE_EXPR_PARTITION_GETTER

    DEFINE_PARTITION_GETTER(ChartUnilevel,   ChartIndex, unilevel_charts)
    DEFINE_PARTITION_GETTER(ChartMultilevel, ChartIndex, multilevel_charts)

    DEFINE_PARTITION_GETTER(OperatorFunctionName, NameIndex, operator_names)

#undef DEFINE_PARTITION_GETTER

    Partition<TypeIndex, Index> File::type_heap() const
    {
        return get_partition<TypeIndex, Index>("heap.type");
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return get_partition<ExprIndex, Index>("heap.expr");
    }

    Partition<DeclIndex> File::deduction_guides() const
    {
        return get_partition<DeclIndex, uint32_t>("name.guide");
    }

    template<typename T, typename Index>
    Partition<T, Index> File::get_partition() const
    {
        return get_partition<T, Index>(T::PartitionName);
    }

    template<typename T, typename Index>
    Partition<T, Index> File::get_partition(std::string_view name) const
    {
        const auto partition = table_of_contents_.at(name);
        assert(static_cast<size_t>(partition->entry_size) == sizeof(T));
        return { get_pointer<T>(partition->offset), raw_count(partition->cardinality) };
    }

    template<typename T>
    T const* File::get_pointer(ByteOffset offset) const
    {
        return static_cast<T const*>(get_raw_pointer(offset));
    }

    void const* File::get_raw_pointer(ByteOffset offset) const
    {
        return fmap_.data() + static_cast<size_t>(offset);
    }

    size_t File::calc_size() const
    {
        auto result = sizeof(Structure) + raw_count(header().string_table_size);
        const auto toc = table_of_contents();
        result += toc.size_bytes();
        for (const auto & partition : toc)
            result += partition.size_bytes();
        return result;
    }

    std::span<PartitionSummary const> File::table_of_contents() const
    {
        auto const & h = header();
        return { get_pointer<PartitionSummary>(h.toc), raw_count(h.partition_count) };
    }

    namespace
    {
        constexpr auto as_bytes(auto... values)
        {
            return std::array { static_cast<std::byte>(values)... };
        }

        constexpr FileSignature CANONICAL_FILE_SIGNATURE = as_bytes(0x54, 0x51, 0x45, 0x1A);
    }

    File const& File::get_imported_module(ModuleReference module) const
    {
        if (auto owner = module.owner; is_null(owner))
        {
            // global module
            return env_->get_module_by_name(get_string(module.partition));
        }
        else
        {
            std::string name = get_string(owner);
            if (auto partition = module.partition; !is_null(partition))
                name.append(":").append(get_string(partition));
            return env_->get_module_by_name(name);
        }
    }

    File::File(std::string const & path, Environment* env)
        : env_(env)
        , fmap_(path)
    {
        if (structure()->signature != CANONICAL_FILE_SIGNATURE)
            throw std::invalid_argument("corrupted file signature");

        if (calc_size() != fmap_.size())
            throw std::runtime_error("corrupted file");

        fill_table_of_contents();
    }

    void File::fill_table_of_contents()
    {
        for (const auto & partition : table_of_contents())
            table_of_contents_.emplace(get_string(partition.name), &partition);
    }
}
