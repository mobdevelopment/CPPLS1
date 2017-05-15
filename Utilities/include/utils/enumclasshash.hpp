#ifndef UTILS_ENUMCLASSHASH_HEADER_INCLUDED
#define UTILS_ENUMCLASSHASH_HEADER_INCLUDED

namespace utils
{
	struct EnumClassHash
	{
		template <typename T>
		std::size_t operator()(T t) const
		{
			return static_cast<std::size_t>(t);
		}
	}; // class EnumClassHash
} // namespace utils

#endif  // UTILS_ENUMCLASSHASH_HEADER_INCLUDED
