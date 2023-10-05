module;

#include <compare>
#include <ranges>

export module reflifc:Module;

import :Scope;
import :ScopeDeclaration;

import reflifc.ViewOf;

import ifc;
import ifc.Environment;
import ifc.Module;
import ifc.FileHeader;
import ifc.Partition;

export namespace reflifc
{
    struct ModuleReference
    {
        ModuleReference(ifc::File const* ifc, ifc::ModuleReference const& module_reference)
            : module_reference_(&module_reference)
            , ifc_(ifc)
        {
        }

        const char* owner() const {
            return get_string_or_null(module_reference_->owner);
        }
        const char* partition() const { 
            return get_string_or_null(module_reference_->partition);
        }

        auto operator<=>(ModuleReference const& other) const = default;

    private:
        const char* get_string_or_null(ifc::TextOffset text) const {
            if (ifc::is_null(text)) {
                return nullptr;
            }
            return ifc_->get_string(text);
        }

        ifc::ModuleReference const* module_reference_;
        ifc::File const* ifc_;
    };

    struct UnitDescription
    {
        UnitDescription(ifc::File const* ifc, ifc::UnitIndex unit)
            : unit_(unit)
            , ifc_(ifc)
        {
        }

        bool is_primary() const { return unit_.sort() == ifc::UnitSort::Primary; }

        const char* name() const { return ifc_->get_string(ifc::TextOffset{unit_.index}); }

        auto operator<=>(UnitDescription const& other) const = default;

    private:
        ifc::UnitIndex unit_;
        ifc::File const* ifc_;
    };

    struct Module
    {
    private:
        ViewOf<Module> auto dereference(ifc::Partition<ifc::ModuleReference, ifc::Index> partition, ifc::Environment& environment) const 
        {
            return partition
                | std::views::transform([ifc = ifc_, &environment] (ifc::ModuleReference const & module_reference) {
                    const auto& other_ifc = environment.get_referenced_module(module_reference, *ifc);
                    return Module(&other_ifc);
                });
        }

    public:
        explicit Module(ifc::File const* ifc)
            : ifc_(ifc)
        {
        }

        ViewOf<ScopeDeclaration> auto scope_declarations() const
        {
            return ifc_->scope_declarations()
                | std::views::transform([ifc = ifc_] (ifc::ScopeDeclaration const & scope) {
                    return ScopeDeclaration(ifc, scope);
                });
        }

        ViewOf<Module> auto exported_modules(ifc::Environment& environment) const
        {
            return dereference(ifc_->exported_modules(), environment);
        }

        ViewOf<Module> auto imported_modules(ifc::Environment& environment) const
        {
            return dereference(ifc_->imported_modules(), environment);
        }

        Scope global_namespace() const
        {
            return { ifc_, ifc_->header().global_scope };
        }

        UnitDescription unit() const
        {
            return { ifc_, ifc_->header().unit };
        }

        auto operator<=>(Module const& other) const = default;

    private:
        ifc::File const* ifc_;
    };
}
