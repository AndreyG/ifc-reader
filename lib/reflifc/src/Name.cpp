#include "reflifc/Name.h"

#include "reflifc/TupleView.h"
#include "reflifc/Declaration.h"
#include "reflifc/Type.h"

#include <ifc/File.h>

namespace reflifc
{
    bool Name::is_identifier() const
    {
        return sort() == ifc::NameSort::Identifier;
    }

    char const* Name::as_identifier() const
    {
        return ifc_->get_string(ifc::TextOffset{index_.index});
    }

    bool Name::is_operator() const
    {
        return sort() == ifc::NameSort::Operator;
    }

    char const* Name::operator_name() const
    {
        const auto operator_function_text = ifc_->operator_names()[index_].encoded;
        return ifc_->get_string(operator_function_text);
    }

    ifc::Operator Name::get_operator() const
    {
        return ifc_->operator_names()[index_].operator_;
    }

    bool Name::is_literal() const
    {
        return sort() == ifc::NameSort::Literal;
    }

    char const* Name::as_literal() const
    {
        const auto literal_text = ifc_->literal_names()[index_].encoded;
        return ifc_->get_string(literal_text);
    }

    bool Name::is_conversion() const
    {
        return sort() == ifc::NameSort::Conversion;
    }

    char const* Name::as_conversion_name() const
    {
        const auto conversion_function_text = ifc_->conversion_function_names()[index_].encoded;
        return ifc_->get_string(conversion_function_text);
    }

    Type Name::get_conversion_target_type() const
    {
        return Type{ ifc_, ifc_->conversion_function_names()[index_].target };
    }

    bool Name::is_template() const
    {
        return sort() == ifc::NameSort::Template;
    }

    Name Name::as_template() const
    {
        return Name{ ifc_, ifc_->template_names()[index_].name };
    }

    bool Name::is_specialization() const
    {
        return sort() == ifc::NameSort::Specialization;
    }

    SpecializationName Name::as_specialization() const
    {
        return { ifc_, ifc_->specialization_names()[index_] };
    }

    bool Name::is_soure_file() const
    {
        return sort() == ifc::NameSort::SourceFile;
    }

    char const* Name::as_source_file() const
    {
        const auto source_filename_text = ifc_->source_file_names()[index_].path;
        return ifc_->get_string(source_filename_text);
    }

    char const* Name::get_source_file_header_guard() const
    {
        const auto guard_text = ifc_->source_file_names()[index_].guard;
        return ifc_->get_string(guard_text);
    }

    bool Name::is_deduction_guide() const
    {
        return sort() == ifc::NameSort::Guide;
    }

    Declaration Name::as_deduction_guide() const
    {
        return Declaration{ ifc_, ifc_->deduction_guide_names()[index_].primary_template };
    }

    Name SpecializationName::primary() const
    {
        return { ifc_, specialization_->primary };
    }

    TupleExpressionView SpecializationName::template_arguments() const
    {
        return { ifc_, specialization_->arguments };
    }
}
