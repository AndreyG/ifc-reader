module;

#include <compare>

export module reflifc:TemplateDeclaration;

import :Chart;
import :Declaration;
import :Name;

import ifc;

namespace reflifc
{
    export struct TemplateDeclaration
    {
        TemplateDeclaration(ifc::File const* ifc, ifc::TemplateDeclaration const& template_)
            : ifc_(ifc)
            , template_(&template_)
        {
        }

        Name name() const { return { ifc_, template_->name }; }
        Declaration entity() const { return { ifc_, template_->entity.decl }; }
        Chart chart() const { return { ifc_, template_->chart }; }
        Declaration home_scope() const { return { ifc_, template_->home_scope }; }
        ifc::Access access() const { return template_->access; }
        ifc::BasicSpecifiers specifiers() const { return template_->specifiers; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(TemplateDeclaration const& other) const = default;

    private:
        ifc::File const* ifc_;
        ifc::TemplateDeclaration const* template_;
    };
}
