#include "ifc/File.h"
#include "ifc/Environment.h"

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

    Partition<ScopeDescriptor, ScopeIndex> File::scope_descriptors() const
    {
        return get_partition<ScopeDescriptor, ScopeIndex>();
    }

    Partition<Declaration, Index> File::declarations() const
    {
        return get_partition<Declaration, Index>();
    }

    Partition<ScopeDeclaration> File::scope_declarations() const
    {
        return get_partition<ScopeDeclaration>();
    }

    Partition<TemplateDeclaration> File::template_declarations() const
    {
        return get_partition<TemplateDeclaration>();
    }

    Partition<UsingDeclaration> File::using_declarations() const
    {
        return get_partition<UsingDeclaration>();
    }

    Partition<Enumeration> File::enumerations() const
    {
        return get_partition<Enumeration>();
    }

    Partition<AliasDeclaration> File::alias_declarations() const
    {
        return get_partition<AliasDeclaration>();
    }

    Partition<DeclIndex> File::deduction_guides() const
    {
        return get_partition<DeclIndex, uint32_t>("name.guide");
    }

    Partition<DeclReference> File::decl_references() const
    {
        return get_partition<DeclReference>();
    }

    Partition<FundamentalType> File::fundamental_types() const
    {
        return get_partition<FundamentalType>();
    }

    Partition<DesignatedType> File::designated_types() const
    {
        return get_partition<DesignatedType>();
    }

    Partition<SyntacticType> File::syntactic_types() const
    {
        return get_partition<SyntacticType>();
    }

    Partition<ExpansionType> File::expansion_types() const
    {
        return get_partition<ExpansionType>();
    }

    Partition<FunctionType> File::function_types() const
    {
        return get_partition<FunctionType>();
    }

    Partition<TupleType> File::tuple_types() const
    {
        return get_partition<TupleType>();
    }

    Partition<LvalueReference> File::lvalue_references() const
    {
        return get_partition<LvalueReference>();
    }

    Partition<RvalueReference> File::rvalue_references() const
    {
        return get_partition<RvalueReference>();
    }

    Partition<QualifiedType> File::qualified_types() const
    {
        return get_partition<QualifiedType>();
    }

    Partition<TypeExpression> File::type_expressions() const
    {
        return get_partition<TypeExpression>();
    }

    Partition<NamedDecl> File::decl_expressions() const
    {
        return get_partition<NamedDecl>();
    }

    Partition<TemplateId> File::template_ids() const
    {
        return get_partition<TemplateId>();
    }

    Partition<TupleExpression> File::tuple_expressions() const
    {
        return get_partition<TupleExpression>();
    }

    Partition<TypeIndex, Index> File::type_heap() const
    {
        return get_partition<TypeIndex, Index>("heap.type");
    }

    Partition<ExprIndex, Index> File::expr_heap() const
    {
        return get_partition<ExprIndex, Index>("heap.expr");
    }

    Partition<FunctionDeclaration> File::functions() const
    {
        return get_partition<FunctionDeclaration>();
    }

    Partition<VariableDeclaration> File::variables() const
    {
        return get_partition<VariableDeclaration>();
    }

    Partition<ParameterDeclaration> File::parameters() const
    {
        return get_partition<ParameterDeclaration>();
    }

    Partition<OperatorFunctionName> File::operator_names() const
    {
        return get_partition<OperatorFunctionName>();
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
        return std::span<T const> { get_pointer<T>(partition->offset), raw_count(partition->cardinality) };
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
