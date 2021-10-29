#pragma once

#include "ifc/FileFwd.h"

#include "ifc/Expression.h"
#include "ifc/Declaration.h"
#include "ifc/Type.h"

#include <iosfwd>

class Presenter
{
public:
    Presenter(ifc::File const & file, std::ostream& out)
        : file_(file)
        , out_(out)
    {}

    void present(ifc::DeclIndex decl) const;

private:
    void present(ifc::NameIndex)     const;
    void present(ifc::DeclReference) const;

    void present(ifc::TypeIndex) const;

    void present(ifc::FunctionType    const &) const;
    void present(ifc::FundamentalType const &) const;

    void present(ifc::SyntacticType) const;
    void present(ifc::TupleType    ) const;
    void present(ifc::QualifiedType) const;
    void present(ifc::Qualifiers) const;

    void present(ifc::LvalueReference) const;
    void present(ifc::RvalueReference) const;

    void present(ifc::NamedDecl const &) const;
    void present(ifc::TupleExpression const &) const;
    void present(ifc::TemplateId const &) const;
    void present(ifc::ExprIndex) const;

    void present_refered_declaration(ifc::DeclIndex) const;

private:
    ifc::File const & file_;
    std::ostream& out_;
};
