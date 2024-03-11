#pragma once
#include <functional>

namespace reflifc
{
	template<typename... Args>
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