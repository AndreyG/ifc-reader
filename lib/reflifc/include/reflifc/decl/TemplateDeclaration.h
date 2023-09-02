#pragma once

#include "reflifc/HashCombine.h"
#include "reflifc/Name.h"

#include <ifc/DeclarationFwd.h>
#include <ifc/FileFwd.h>

namespace reflifc
{
    struct Chart;
    struct Declaration;

    struct TemplateDeclaration
    {
        TemplateDeclaration(ifc::File const* ifc, ifc::TemplateDeclaration const& template_)
            : ifc_(ifc)
            , template_(&template_)
        {
        }

        Name name() const;
        Declaration entity() const;
        Chart chart() const;
        Declaration home_scope() const;
        ifc::Access access() const;
        ifc::BasicSpecifiers specifiers() const;

        auto operator<=>(TemplateDeclaration const& other) const = default;

    private:
        friend std::hash<TemplateDeclaration>;

        ifc::File const* ifc_;
        ifc::TemplateDeclaration const* template_;
    };
}

template<>
struct std::hash<reflifc::TemplateDeclaration>
{
    size_t operator()(reflifc::TemplateDeclaration const& template_decl) const noexcept
    {
        return reflifc::hash_combine(0, template_decl.ifc_, template_decl.template_);
    }
};
