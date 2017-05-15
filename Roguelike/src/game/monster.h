#ifndef GAME_MONSTER_HEADER_INCLUDED
#define GAME_MONSTER_HEADER_INCLUDED

#include <system_error>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include <boost/filesystem.hpp>

#include "errorcategory.h"

namespace game
{
	class Monster;

	typedef std::unordered_map<int, Monster> MonstersContainer;

	class Monster
	{
	public:
		static const int boss = -1;

		std::string		name;
		int				rand			= 0;
		int				level			= 0;
		int				minDamage		= 0;
		int				maxDamage		= 0;
		int				attackChance	= 0;
		int				attackAmount	= 0;
		int				defenseChance	= 0;
		int				lifePoints		= 0;
	}; // class Hero

	class SaveMonster
	{
	public:
		std::string		name;
		int				x;
		int				y;
		int				z;
		int				hp;
	};

	MonstersContainer ParseMonster(std::istream& stream);
	MonstersContainer ParseMonster(std::istream& stream, std::error_code& errorBuffer);

	MonstersContainer GetSavedMonsters();
}

#endif // #ifndef GAME_MONSTER_HEADER_INCLUDED
