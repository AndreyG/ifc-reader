module;

#include <functional>

export module reflifc.HashCombine;

import ifc.AbstractReference;

namespace reflifc
{
	export template<typename... Args>
	size_t hash_combine(size_t seed, Args const&... args) noexcept
	{
		// Implementation inspired from Boost.
		auto hash_combine_single = [&seed]<typename Arg>(Arg const& arg)
		{
			seed ^= std::hash<Arg>{}(arg) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		};

		(hash_combine_single(args), ...);

		return seed;
	}
}

export template<int N, typename Sort>
struct std::hash<ifc::AbstractReference<N, Sort>>
{
	std::size_t operator()(ifc::AbstractReference<N, Sort> s) const noexcept
	{
		using std::uint32_t;
		return std::hash<uint32_t>{}(reinterpret_cast<uint32_t&>(s));
	}
};
