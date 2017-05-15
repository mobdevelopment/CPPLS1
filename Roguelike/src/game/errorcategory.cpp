#include "errorcategory.h"

using namespace game;

const char* ErrorCategory::name() const noexcept
{
	return "game";
}

std::string ErrorCategory::message(int ev) const
{
	switch ((Error)ev)
	{
	case Error::SUCCESS:
		return "Success";
	case Error::STREAM_ERROR:
		return "Stream error";
	case Error::GAME_ALREADY_RUNNING:
		return "Game already running";
	case Error::GAME_NOT_RUNNING:
		return "Game not running";
	case Error::GAME_NOT_CLEARED:
		return "Game not cleared";
	case Error::DUNGEON_PARAMETER_ZERO_VALUE:
		return "Dungeon parameter zero value";
	default:
		return "Unknown game error";
	}
}

const std::error_category& game::GetErrorCategory()
{
	static ErrorCategory instance;
	return instance;
}

std::error_code std::make_error_code(game::Error error)
{
	return std::error_code(static_cast<int>(error), game::GetErrorCategory());
}

std::error_condition std::make_error_condition(game::Error error)
{
	return std::error_condition(static_cast<int>(error), game::GetErrorCategory());
}