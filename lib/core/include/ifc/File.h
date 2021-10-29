#pragma once

#include "FileHeader.h"
#include "Partition.h"

#include "ChartFwd.h"
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
        Partition<Declaration, Index>               declarations()          const;
        Partition<ScopeDeclaration, DeclIndex>      scope_declarations()    const;
        Partition<TemplateDeclaration, DeclIndex>   template_declarations() const;
        Partition<UsingDeclaration, DeclIndex>      using_declarations()    const;
        Partition<Enumeration, DeclIndex>           enumerations()          const;
        Partition<AliasDeclaration, DeclIndex>      alias_declarations()    const;
        Partition<FunctionDeclaration, DeclIndex>   functions()             const;
        Partition<VariableDeclaration, DeclIndex>   variables()             const;
        Partition<ParameterDeclaration, DeclIndex>  parameters()            const;
        Partition<DeclReference, DeclIndex>         decl_references()       const;
        Partition<DeclIndex>                        deduction_guides()      const;

        // Types
        Partition<FundamentalType, TypeIndex>   fundamental_types()     const;
        Partition<DesignatedType, TypeIndex>    designated_types()      const;
        Partition<SyntacticType, TypeIndex>     syntactic_types()       const;
        Partition<ExpansionType, TypeIndex>     expansion_types()       const;
        Partition<FunctionType, TypeIndex>      function_types()        const;
        Partition<TupleType, TypeIndex>         tuple_types()           const;
        Partition<LvalueReference, TypeIndex>   lvalue_references()     const;
        Partition<RvalueReference, TypeIndex>   rvalue_references()     const;
        Partition<QualifiedType, TypeIndex>     qualified_types()       const;
        Partition<ForallType, TypeIndex>        forall_types()          const;

        // Expressions
        Partition<TypeExpression, ExprIndex>    type_expressions()      const;
        Partition<NamedDecl, ExprIndex>         decl_expressions()      const;
        Partition<TemplateId, ExprIndex>        template_ids()          const;
        Partition<TupleExpression, ExprIndex>   tuple_expressions()     const;

        // Heaps
        Partition<TypeIndex, Index>             type_heap()             const;
        Partition<ExprIndex, Index>             expr_heap()             const;

        // Names
        Partition<OperatorFunctionName, NameIndex> operator_names()     const;

        // Charts
        Partition<ChartUnilevel, ChartIndex>    unilevel_charts()       const;
        Partition<ChartMultilevel, ChartIndex>  multilevel_charts()     const;

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
