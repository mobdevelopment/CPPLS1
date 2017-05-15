#include "errorcategory.h"

const char* utils::cmd::ErrorCategory::name() const noexcept
{
	return "utils command";
}

std::string utils::cmd::ErrorCategory::message(int ev) const
{
	switch ((Error)ev)
	{
	case Error::SUCCESS:
		return "Success";
	case Error::COMMAND_NOT_REGISTERED:
		return "Command not registered";
	case Error::STREAM_ERROR:
		return "Stream error";
	case Error::INVALID_INPUT_FORMAT:
		return "Invalid input format";
	default:
		return "Unknown utils command error";
	}
}

const std::error_category& utils::cmd::GetErrorCategory()
{
	static ErrorCategory instance;
	return instance;
}

std::error_code std::make_error_code(utils::cmd::Error error)
{
	return std::error_code(static_cast<int>(error), utils::cmd::GetErrorCategory());
}

std::error_condition std::make_error_condition(utils::cmd::Error error)
{
	return std::error_condition(static_cast<int>(error), utils::cmd::GetErrorCategory());
}