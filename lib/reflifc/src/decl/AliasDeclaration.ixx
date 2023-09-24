export module reflifc:AliasDeclaration;

import :Declaration;
import :Type;

import reflifc.HashCombine;

import ifc;

namespace reflifc
{
    export struct AliasDeclaration
    {
        AliasDeclaration(ifc::File const* ifc, ifc::AliasDeclaration const& alias)
            : ifc_(ifc)
            , alias_(&alias)
        {
        }

        char const* name()      const { return ifc_->get_string(alias_->name); }
        Type        aliasee()   const { return { ifc_, alias_->aliasee }; }
        Declaration home_scope()const { return { ifc_, alias_->home_scope }; }
        ifc::Access access()    const { return alias_->access; }

        ifc::File const* containing_file() const { return ifc_; }

        auto operator<=>(AliasDeclaration const& other) const = default;

    private:
        friend std::hash<AliasDeclaration>;

        ifc::File const* ifc_;
        ifc::AliasDeclaration const* alias_;
    };
}

template<>
struct std::hash<reflifc::AliasDeclaration>
{
    size_t operator()(reflifc::AliasDeclaration alias) const noexcept
    {
        return reflifc::hash_combine(0, alias.ifc_, alias.alias_);
    }
};
