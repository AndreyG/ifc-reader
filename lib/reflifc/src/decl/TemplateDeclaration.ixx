module;

#include <functional>

export module reflifc:TemplateDeclaration;

import :Chart;
import :Declaration;
import :Name;
import reflifc.HashCombine;

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
        friend std::hash<TemplateDeclaration>;

        ifc::File const* ifc_;
        ifc::TemplateDeclaration const* template_;
    };
}

template<>
struct std::hash<reflifc::TemplateDeclaration>
{
    size_t operator()(reflifc::TemplateDeclaration template_decl) const noexcept
    {
        return reflifc::hash_combine(0, template_decl.ifc_, template_decl.template_);
    }
};
