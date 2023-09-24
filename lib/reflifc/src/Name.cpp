module reflifc;

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
        const auto operator_function_name = ifc_->operator_names()[index_];
        return ifc_->get_string(operator_function_name.encoded);
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
        return ifc_->get_string(ifc_->literal_names()[index_].encoded);
    }

    bool Name::is_specialization() const
    {
        return sort() == ifc::NameSort::Specialization;
    }

    SpecializationName Name::as_specialization() const
    {
        return { ifc_, ifc_->specialization_names()[index_] };
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
