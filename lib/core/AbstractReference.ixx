module;

#include <functional>
#include <type_traits>
#include <cstdint>
#include <compare>

export module ifc.AbstractReference;

namespace ifc
{
    using std::uint32_t;

    export template<int N, typename _Sort>
        requires std::is_enum_v<_Sort>
    struct AbstractReference
    {
        using Sort = _Sort;

        union
        {
	        struct
	        {
	        	uint32_t tag    : N;
	        	uint32_t index  : 32 - N;		        
	        };
            uint32_t raw;
        };

        Sort sort() const
        {
            return static_cast<Sort>(tag);
        }

        bool is_null() const
        {
            return raw == 0;
        }

    	friend auto operator==(AbstractReference a, AbstractReference b)
        {
            return a.raw == b.raw;
        }

        friend auto operator<=>(AbstractReference a, AbstractReference b)
        {
            return a.raw <=> b.raw;
        }
    };
}
