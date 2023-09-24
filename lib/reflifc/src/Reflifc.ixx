export module reflifc;

// top-level entities

export import :Attribute;
export import :Chart;
export import :Declaration;
export import :Expression;
export import :Module;
export import :Name;
export import :Syntax;
export import :TemplateId;
export import :Type;

// declarations

export import :AliasDeclaration;
export import :ClassOrStruct;
export import :Concept;
export import :DeclarationReference;
export import :Enumeration;
export import :Enumerator;
export import :Function;
export import :Intrinsic;
export import :Namespace;
export import :Scope;
export import :ScopeDeclaration;
export import :Specialization;
export import :TemplateDeclaration;
export import :UsingDeclaration;

// expressions

export import :MonadExpression;
export import :DyadExpression;
export import :UnqualifiedIdExpression;
export import :QualifiedNameExpression;
export import :CallExpression;
export import :Sizeof;
export import :Alignof;
export import :RequiresExpression;
export import :PathExpression;
export import :ReadExpression;
export import :ProductValueTypeExpression;

// types

export import :ArrayType;
export import :ExpansionType;
export import :FunctionType;
export import :ForallType;
export import :PlaceholderType;
export import :Pointer;
export import :Reference;
export import :QualifiedType;

// syntax

export import :TemplateIdSyntax;
export import :TypeId;
export import :TypeSpecifier;
export import :TypeTraitIntrinsic;