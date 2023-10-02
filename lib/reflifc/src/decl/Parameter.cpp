module;

#include <cassert>

module reflifc;

namespace reflifc
{
	Chart Parameter::template_parameters() const
	{
		auto forall_type = type().as_forall();
		assert(forall_type.subject().as_fundamental().basis == ifc::TypeBasis::Typename);
		return forall_type.chart();	        
	}
}