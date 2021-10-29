#pragma once

#include "FileHeader.h"
#include "Partition.h"

#include "ExpressionFwd.h"
#include "DeclarationFwd.h"
#include "NameFwd.h"
#include "TypeFwd.h"
#include "Indices.h"

#include <boost/iostreams/device/mapped_file.hpp>

#include <unordered_map>

namespace ifc
{
    class File
    {
    public:
        FileHeader const & header() const;

        const char * get_string(TextOffset) const;

        ScopeDescriptor global_scope() const;

        Partition<ScopeDescriptor, ScopeIndex>  scope_descriptors()     const;

        // Declarations
        Partition<Declaration, Index>           declarations()          const;
        Partition<ScopeDeclaration>             scope_declarations()    const;
        Partition<TemplateDeclaration>          template_declarations() const;
        Partition<UsingDeclaration>             using_declarations()    const;
        Partition<Enumeration>                  enumerations()          const;
        Partition<AliasDeclaration>             alias_declarations()    const;
        Partition<FunctionDeclaration>          functions()             const;
        Partition<VariableDeclaration>          variables()             const;
        Partition<ParameterDeclaration>         parameters()            const;
        Partition<DeclIndex>                    deduction_guides()      const;
        Partition<DeclReference>                decl_references()       const;

        // Types
        Partition<FundamentalType>              fundamental_types()     const;
        Partition<DesignatedType>               designated_types()      const;
        Partition<SyntacticType>                syntactic_types()       const;
        Partition<FunctionType>                 function_types()        const;
        Partition<TupleType>                    tuple_types()           const;
        Partition<LvalueReference>              lvalue_references()     const;
        Partition<RvalueReference>              rvalue_references()     const;
        Partition<QualifiedType>                qualified_types()       const;

        // Expressions
        Partition<TypeExpression>               type_expressions()      const;
        Partition<NamedDecl>                    decl_expressions()      const;
        Partition<TemplateId>                   template_ids()          const;
        Partition<TupleExpression>              tuple_expressions()     const;

        // Heaps
        Partition<TypeIndex, Index>             type_heap()             const;
        Partition<ExprIndex, Index>             expr_heap()             const;

        // Names
        Partition<OperatorFunctionName>         operator_names()        const;

        File const & get_imported_module(ModuleReference) const;

        File(std::string const &, class Environment*);

    private:
        struct Structure;

        Structure const * structure() const;

        template<typename T, typename Index = uint32_t>
        Partition<T, Index> get_partition() const;

        template<typename T, typename Index>
        Partition<T, Index> get_partition(std::string_view name) const;

        template<typename T>
        T const* get_pointer(ByteOffset offset) const;

        void const* get_raw_pointer(ByteOffset) const;

        size_t calc_size() const;

        std::span<PartitionSummary const> table_of_contents() const;

        void fill_table_of_contents();

    private:
        Environment* env_;
        boost::iostreams::mapped_file_source fmap_;
        std::unordered_map<std::string_view, PartitionSummary const*> table_of_contents_;
    };
}
