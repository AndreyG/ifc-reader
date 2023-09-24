module reflifc;

namespace reflifc
{
    ifc::Sequence ChartUnilevel::params_sequence() const
    {
        return *unilevel_;
    }

    bool ChartUnilevel::has_constraint() const
    {
        return !unilevel_->constraint.is_null();
    }

    Expression ChartUnilevel::constraint() const
    {
        return { ifc_, unilevel_->constraint };
    }

    ChartUnilevel Chart::as_unilevel() const
    {
        return { ifc_, ifc_->unilevel_charts()[index_] };
    }
}
