#ifndef UTILS_CMD_ERROR_HEADER_INCLUDED
#define UTILS_CMD_ERROR_HEADER_INCLUDED

#include <system_error>
#include <string>

namespace utils
{
namespace cmd
{
	enum class Error
	{
		SUCCESS,
		COMMAND_NOT_REGISTERED,
		STREAM_ERROR,
		INVALID_INPUT_FORMAT
	}; // enum class Error

	class ErrorCategory :
		public std::error_category
	{
	public:
		virtual const char* name() const noexcept;
		virtual std::string message(int ev) const;
	}; // class ErrorCategory

	const std::error_category& GetErrorCategory();
} // namespace cmd
} // namespace utils

namespace std
{
	template <>
	struct is_error_code_enum<utils::cmd::Error> :
		public true_type {};

	error_code make_error_code(utils::cmd::Error error);
	error_condition make_error_condition(utils::cmd::Error error);
} // namespace std

#endif // #ifndef UTILS_CMD_ERROR_HEADER_INCLUDED