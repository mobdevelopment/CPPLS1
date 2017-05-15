#ifndef GAME_ERRORCATEGORY_HEADER_INCLUDED
#define GAME_ERRORCATEGORY_HEADER_INCLUDED

#include <system_error>
#include <string>

#include "error.h"

namespace game
{
	class ErrorCategory :
		public std::error_category
	{
	public:
		virtual const char* name() const noexcept;
		virtual std::string message(int ev) const;
	}; // class ErrorCategory

	const std::error_category& GetErrorCategory();
} // namespace game

namespace std
{
	template <>
	struct is_error_code_enum<game::Error> :
		public true_type {};

	error_code make_error_code(game::Error error);
	error_condition make_error_condition(game::Error error);
} // namespace std

#endif // #ifndef GAME_ERRORCATEGORY_HEADER_INCLUDED
