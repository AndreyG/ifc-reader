#pragma once

#include "DeclarationFwd.h"

#include "CallingConvention.h"
#include "ChartFwd.h"
#include "ExpressionFwd.h"
#include "FileFwd.h"
#include "Module.h"
#include "Name.h"
#include "NoexceptSpecification.h"
#include "Scope.h"
#include "SourceLocation.h"
#include "TypeFwd.h"

namespace ifc
{
    using std::uint8_t;
    using std::uint16_t;

    enum class Access : uint8_t
    {
        None,
        Private,
        Protected,
        Public
    };

    enum class BasicSpecifiers : uint8_t
    {
        Cxx                     = 0,      // C++ language linkage
        C                       = 1 << 0, // C language linkage
        Internal                = 1 << 1, //
        Vague                   = 1 << 2, // Vague linkage, e.g. COMDAT, still external
        External                = 1 << 3, // External linkage.
        Deprecated              = 1 << 4, // [[deprecated("foo")]]
        InitializedInClass      = 1 << 5, // defined or initialized in a class
        NonExported             = 1 << 6, // Not explicitly exported
        IsMemberOfGlobalModule  = 1 << 7 // member of the global module
    };

    enum class ReachableProperties : uint8_t
    {
        None                = 0,        // nothing beyond name, type, scope.
        Initializer         = 1 << 0,   // IPR-initializer exported.
        DefaultArguments    = 1 << 1,   // function or template default arguments exported
        Attributes          = 1 << 2,   // standard attributes exported.
        All                 = 0xff,     // Everything.
    };

    enum class ObjectTraits : uint8_t {
        None                = 0,
        Constexpr           = 1 << 0,
        Mutable             = 1 << 1,
        ThreadLocal         = 1 << 2,
        Inline              = 1 << 3,
        InitializerExported = 1 << 4,
        Vendor              = 1 << 7,
    };

    enum class ParameterLevel : uint32_t { };

    enum class ParameterPosition : uint32_t { };

    enum class DeclSort : uint32_t
    {
        VendorExtension         = 0x00,
        Enumerator              = 0x01,
        Variable                = 0x02,
        Parameter               = 0x03,
        Field                   = 0x04,
        Bitfield                = 0x05,
        Scope                   = 0x06,
        Enumeration             = 0x07,
        Alias                   = 0x08,
        Temploid                = 0x09,
        Template                = 0x0A,
        PartialSpecialization   = 0x0B,
        Specialization          = 0x0C,
        DefaultArgument         = 0x0D,
        Concept                 = 0x0E,
        Function                = 0x0F,
        Method                  = 0x10,
        Constructor             = 0x11,
        InheritedConstructor    = 0x12,
        Destructor              = 0x13,
        Reference               = 0x14,
        UsingDeclaration        = 0x15,
        UsingDirective          = 0x16,
        Friend                  = 0x17,
        Expansion               = 0x18,
        DeductionGuide          = 0x19,
        Barren                  = 0x1A,
        Tuple                   = 0x1B,
        SyntaxTree              = 0x1C,
        Intrinsic               = 0x1D,
        Property                = 0x1E,
        OutputSegment           = 0x1F,
    };

    struct Declaration
    {
        DeclIndex index;

        PARTITION_NAME("scope.member");
    };

    struct UsingDeclaration
    {
        NameIndex name;
        SourceLocation locus;
        DeclIndex home_scope;
        DeclIndex resolution;
        ExprIndex parent;
        TextOffset name2;
        BasicSpecifiers specifiers;
        Access access;
        bool hidden;

        PARTITION_NAME("decl.using-declaration");
        PARTITION_SORT(DeclSort::UsingDeclaration);
    };

    struct ParameterizedEntity
    {
        DeclIndex decl;
        SentenceIndex head;
        SentenceIndex body;
        SentenceIndex attributes;
    };

    struct TemplateDeclaration
    {
        NameIndex name;
        SourceLocation locus;
        DeclIndex home_scope;
        ChartIndex chart;
        ParameterizedEntity entity;
        TypeIndex type;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.template");
        PARTITION_SORT(DeclSort::Template);
    };

    struct SpecializationForm
    {
        DeclIndex primary;
        ExprIndex arguments;

        PARTITION_NAME("form.spec");
    };

    struct PartialSpecialization
    {
        NameIndex name;
        SourceLocation locus;
        DeclIndex home_scope;
        ChartIndex chart;
        ParameterizedEntity entity;
        SpecFormIndex form;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.partial-specialization");
        PARTITION_SORT(DeclSort::PartialSpecialization);
    };

    enum class SpecializationSort : uint8_t
    {
        Implicit        = 0x0,
        Explicit        = 0x1,
        Instantiation   = 0x2,
    };

    struct Specialization
    {
        SpecFormIndex form;
        DeclIndex decl;
        SpecializationSort sort;

        PARTITION_NAME("decl.specialization");
        PARTITION_SORT(DeclSort::Specialization);
    };

    struct Enumeration
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        TypeIndex base;
        Sequence initializer;
        DeclIndex home_scope; 
        ExprIndex alignment;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.enum");
        PARTITION_SORT(DeclSort::Enumeration);
    };

    struct Enumerator
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        ExprIndex initializer;
        BasicSpecifiers specifier;
        Access access;

        PARTITION_NAME("decl.enumerator");
        PARTITION_SORT(DeclSort::Enumerator);
    };

    struct AliasDeclaration
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope;
        TypeIndex aliasee;
        BasicSpecifiers specifiers;
        Access access;

        PARTITION_NAME("decl.alias");
        PARTITION_SORT(DeclSort::Alias);
    };

    enum class PackSize : uint16_t {};

    enum class ScopeTraits : uint8_t
    {
        None                = 0,
        Unnamed             = 1 << 0,
        Inline              = 1 << 1,
        InitializerExported = 1 << 2,
        ClosureType         = 1 << 3,
        Vendor              = 1 << 7,
    };

    struct ScopeDeclaration
    {
        NameIndex name;
        SourceLocation locus;
        TypeIndex type;
        TypeIndex base;
        ScopeIndex initializer;
        DeclIndex home_scope;
        ExprIndex alignment;
        PackSize pack_size;
        BasicSpecifiers specifiers;
        ScopeTraits traits;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.scope");
        PARTITION_SORT(DeclSort::Scope);
    };

    constexpr bool is_inline(ScopeDeclaration const & scope)
    {
        return (static_cast<uint8_t>(scope.traits) & static_cast<uint8_t>(ScopeTraits::Inline)) != 0;
    }

    TypeBasis get_kind(ScopeDeclaration const &, File const &);

    enum class FunctionTraits : uint16_t
    {
        None            = 0,
        Inline          = 1 << 0,
        Constexpr       = 1 << 1,
        Explicit        = 1 << 2,
        Virtual         = 1 << 3,
        NoReturn        = 1 << 4,
        PureVirtual     = 1 << 5,
        HiddenFriend    = 1 << 6,
        Defaulted       = 1 << 7,
        Deleted         = 1 << 8,
        Constrained     = 1 << 9,
        Immediate       = 1 << 10,

        Vendor          = 1 << 15,
    };

    struct FunctionDeclarationBase
    {
        NameIndex name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope;
        ChartIndex chart;
        FunctionTraits traits;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;
    };

    struct FunctionDeclaration : FunctionDeclarationBase
    {
        PARTITION_NAME("decl.function");
        PARTITION_SORT(DeclSort::Function);
    };

    struct MethodDeclaration : FunctionDeclarationBase
    {
        PARTITION_NAME("decl.method");
        PARTITION_SORT(DeclSort::Method);
    };

    struct Constructor
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope;
        ChartIndex chart;
        FunctionTraits traits;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.constructor");
        PARTITION_SORT(DeclSort::Constructor);
    };

    struct Destructor
    {
        TextOffset name;
        SourceLocation locus;
        DeclIndex home_scope;
        NoexceptSpecification eh_spec;
        FunctionTraits traits;
        BasicSpecifiers specifiers;
        Access access;
        CallingConvention convention;
        ReachableProperties properties;

        PARTITION_NAME("decl.destructor");
        PARTITION_SORT(DeclSort::Destructor);
    };

    struct VariableDeclaration
    {
        NameIndex name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope; 
        ExprIndex initializer;
        ExprIndex alignment;
        ObjectTraits traits;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.variable");
        PARTITION_SORT(DeclSort::Variable);
    };

    struct FieldDeclaration
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope;
        ExprIndex initializer;
        ExprIndex alignment;
        ObjectTraits traits;
        BasicSpecifiers specifiers;
        Access access;
        ReachableProperties properties;

        PARTITION_NAME("decl.field");
        PARTITION_SORT(DeclSort::Field);
    };

    enum class ParameterSort : uint8_t
    {
        Object,     // Function parameter
        Type,       // Type template parameter
        NonType,    // Non-type template parameter
        Template,   // Template template parameter
    };

    struct ParameterDeclaration
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        ExprIndex constraint;
        ExprIndex initializer;
        ParameterLevel level;
        ParameterPosition position;
        ParameterSort sort;
        ReachableProperties properties;

        PARTITION_NAME("decl.parameter");
        PARTITION_SORT(DeclSort::Parameter);
    };

    struct FriendDeclaration
    {
        ExprIndex entity;

        PARTITION_NAME("decl.friend");
        PARTITION_SORT(DeclSort::Friend);
    };

    struct Concept
    {
        TextOffset name;
        SourceLocation locus;
        DeclIndex home_scope;
        TypeIndex type;
        ChartIndex chart;
        ExprIndex constraint;
        BasicSpecifiers specifiers;
        Access access;
        SentenceIndex head;
        SentenceIndex body;

        PARTITION_NAME("decl.concept");
        PARTITION_SORT(DeclSort::Concept);
    };

    struct IntrinsicDeclaration
    {
        TextOffset name;
        SourceLocation locus;
        TypeIndex type;
        DeclIndex home_scope;
        BasicSpecifiers specifiers;
        Access access;

        PARTITION_NAME("decl.intrinsic");
        PARTITION_SORT(DeclSort::Intrinsic);
    };

    struct DeclReference
    {
        ModuleReference unit;
        DeclIndex local_index;

        PARTITION_NAME("decl.reference");
        PARTITION_SORT(DeclSort::Reference);
    };
}
