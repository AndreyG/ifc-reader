#pragma once

#include "ifc/ChartFwd.h"
#include "ifc/ExpressionFwd.h"
#include "ifc/TypeFwd.h"

#include "ifc/Declaration.h"
#include "ifc/Partition.h"

#include "ifc/FileFwd.h"

#include <iosfwd>

class Presenter
{
public:
    Presenter(ifc::File const & file, std::ostream& out)
        : file_(file)
        , out_(out)
    {}

    void present_scope_members(ifc::ScopeDescriptor) const;

private:
    void present(ifc::NameIndex)     const;
    void present(ifc::DeclIndex)     const;
    void present(ifc::DeclReference) const;
    void present(ifc::Declaration)   const;

    void present(ifc::TypeIndex) const;

    void present(ifc::FunctionType    const &) const;
    void present(ifc::MethodType      const &) const;
    void present_function_type(auto const &)   const;
    void present(ifc::FunctionTypeTraits)      const;

    void present(ifc::FundamentalType const &) const;

    void present(ifc::SyntacticType) const;
    void present(ifc::ExpansionType) const;
    void present(ifc::TupleType    ) const;
    void present(ifc::QualifiedType) const;
    void present(ifc::Qualifiers) const;

    void present(ifc::LvalueReference) const;
    void present(ifc::RvalueReference) const;

    void present(ifc::NamedDecl const &) const;
    void present(ifc::TupleExpression const &) const;
    void present(ifc::TemplateId const &) const;
    void present(ifc::ExprIndex) const;

    void present(ifc::ChartIndex) const;

    void present_refered_declaration(ifc::DeclIndex) const;

    void present(ifc::ScopeDeclaration      const &) const;
    void present(ifc::FunctionDeclaration   const &) const;
    void present(ifc::MethodDeclaration     const &) const;
    void present(ifc::VariableDeclaration   const &) const;
    void present(ifc::TemplateDeclaration   const &) const;
    void present(ifc::Enumeration           const &) const;
    void present(ifc::AliasDeclaration      const &) const;
    void present(ifc::UsingDeclaration      const &) const;

    template<typename T, typename Index>
    void present_heap_slice(ifc::Partition<T, Index>, ifc::Sequence) const;

    template<typename Range>
    void present_range(Range, std::string_view separator) const;

    void insert_indent() const;

private:
    ifc::File const & file_;
    std::ostream& out_;
    mutable size_t indent_ = 0;
};
