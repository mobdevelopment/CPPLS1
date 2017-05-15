#ifndef GAME_ERROR_HEADER_INCLUDED
#define GAME_ERROR_HEADER_INCLUDED

#include <system_error>
#include <string>

#include "error.h"

namespace game
{
	enum class Error
	{
		SUCCESS,
		STREAM_ERROR,
		GAME_ALREADY_RUNNING,
		GAME_NOT_RUNNING,
		GAME_NOT_CLEARED,
		DUNGEON_PARAMETER_ZERO_VALUE
	}; // enum class Error
}

#endif // #ifndef GAME_ERROR_HEADER_INCLUDED
