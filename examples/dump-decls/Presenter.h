#pragma once

#include "ifc/AttributeFwd.h"
#include "ifc/ChartFwd.h"
#include "ifc/ExpressionFwd.h"
#include "ifc/TypeFwd.h"
#include "ifc/SyntaxTreeFwd.h"

#include "ifc/Declaration.h"
#include "ifc/Literal.h"
#include "ifc/Partition.h"
#include "ifc/Word.h"

#include "ifc/FileFwd.h"

#include <iosfwd>

class Presenter
{
public:
    Presenter(ifc::File const & file, std::ostream& out)
        : file_(file)
        , out_(out)
    {}

    void present_scope_members(ifc::Sequence) const;

private:
    void present(ifc::NameIndex)     const;
    void present(ifc::DeclIndex)     const;
    void present(ifc::DeclReference) const;
    void present(ifc::Declaration)   const;

    void present(ifc::TypeIndex) const;

    void present(ifc::BaseType        const &) const;
    void present(ifc::FunctionType    const &) const;
    void present(ifc::MethodType      const &) const;
    void present_function_type(auto const &)   const;
    void present(ifc::FunctionTypeTraits)      const;

    void present(ifc::AttrIndex) const;
    void present(ifc::AttrScoped    const&) const;
    void present(ifc::AttrLabeled   const&) const;
    void present(ifc::AttrCalled    const&) const;
    void present(ifc::AttrFactored  const&) const;
    void present(ifc::AttrTuple     const&) const;

    void present(ifc::Word const &) const;

    void present(ifc::SourceDirective) const;
    void present(ifc::SourcePunctuator) const;
    void present(ifc::SourceLiteral, ifc::Index const &) const;
    void present(ifc::SourceOperator) const;
    void present(ifc::SourceKeyword) const;
    void present(ifc::SourceIdentifier, ifc::Index const&) const;

    void present(ifc::FundamentalType const &) const;

    void present(ifc::SyntacticType) const;
    void present(ifc::ExpansionType) const;
    void present(ifc::PointerType)   const;
    void present(ifc::TupleType    ) const;
    void present(ifc::QualifiedType) const;
    void present(ifc::Qualifiers) const;
    void present(ifc::PlaceholderType) const;
    void present(ifc::TypenameType) const;
    void present(ifc::DecltypeType) const;

    void present(ifc::LvalueReference) const;
    void present(ifc::RvalueReference) const;

    void present(ifc::NamedDecl const &) const;
    void present(ifc::UnqualifiedId const &) const;
    void present(ifc::QualifiedNameExpression const&) const;
    void present(ifc::TupleExpression const &) const;
    void present(ifc::PathExpression const&) const;
    void present(ifc::TemplateId const &) const;
    void present(ifc::DyadExpression const &) const;
    void present(ifc::CallExpression const&) const;
    void present(ifc::SizeofExpression const &) const;
    void present(ifc::AlignofExpression const &) const;
    void present(ifc::RequiresExpression const&) const;
    void present(ifc::PackedTemplateArguments const &) const;
    void present(ifc::LitIndex) const;
    void present(ifc::ExprIndex) const;
    void present(ifc::StringIndex) const;

    void present(ifc::ChartIndex) const;

    void present_refered_declaration(ifc::DeclIndex) const;

    void present(ifc::ScopeDeclaration      const &, ifc::DeclIndex) const;
    void present(ifc::FunctionDeclaration   const &) const;
    void present(ifc::MethodDeclaration     const &) const;
    void present(ifc::Constructor           const &) const;
    void present(ifc::Destructor            const &) const;
    void present(ifc::VariableDeclaration   const &) const;
    void present(ifc::FieldDeclaration      const &) const;
    void present(ifc::TemplateDeclaration   const &) const;
    void present(ifc::Enumeration           const &) const;
    void present(ifc::AliasDeclaration      const &) const;
    void present(ifc::UsingDeclaration      const &) const;
    void present(ifc::Concept               const &) const;
    void present(ifc::IntrinsicDeclaration  const &) const;
    void present(ifc::FriendDeclaration     const &) const;

    void present(ifc::SyntaxIndex) const;

    void present(ifc::SimpleTypeSpecifier       const &) const;
    void present(ifc::TypeSpecifierSeq          const &) const;
    void present(ifc::DeclSpecifierSeq          const &) const;
    void present(ifc::TypeIdSyntax              const &) const;
    void present(ifc::DeclaratorSyntax          const &) const;
    void present(ifc::PointerDeclaratorSyntax   const &) const;

    void present_function_parameters(ifc::SyntaxIndex parameters) const;
    void present_function_parameter (ifc::SyntaxIndex parameter ) const;

    void present_requirements(ifc::SyntaxIndex requirements) const;
    void present_requirement (ifc::SyntaxIndex requirement ) const;
    void present_compound_requirement(ifc::CompoundRequirementSyntax const &) const;

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
