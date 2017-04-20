#ifndef GAME_SAVE_HEADER_INCLUDED
#define GAME_SAVE_HEADER_INCLUDED

#include <system_error>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include "game.h"
#include "monster.h"

#include "items/item.h"
//#include "items/consumable.h"
//#include "items/equipment.h"
#include <boost/filesystem.hpp>

#include "errorcategory.h"

namespace game
{

	class Game;
	class Save;

	typedef std::unordered_map<std::string, Save> SavesContainer;
	typedef std::unordered_map<int, SaveMonster> SavedMonstersContainer;
	typedef std::unordered_map<int, items::SaveItem> SavedItemsContainer;

	class Save
	{
	public:
		Save();
		~Save();

		std::string		name;
		int				seed;
		int				height;
		int				width;
		int				layers;

		std::string		heroName;
		int				startX;
		int				startY;
		int				startZ;

		SavedMonstersContainer	monsters;
		SavedItemsContainer		bag;
		SavedItemsContainer		equipment;
		SavedItemsContainer		items;

	}; // class Hero

	Save ParseSave(std::istream& stream);
	Save ParseSave(std::istream& stream, std::error_code& errorBuffer);

	void WriteSave(std::ostream& stream, const Save& save);
	void WriteSave(std::ostream& stream, const Save& save, std::error_code& errorBuffer);

	SavesContainer GetSavedSaves();

	Save GetSavedGame(std::string date);
	Save GetSavedGame(std::string date, std::error_code& errorBuffer);

	void SaveGame(const Save& save);
	void SaveGame(const Save& save, std::error_code& errorBuffer);


}

#endif // #ifndef GAME_SAVE_HEADER_INCLUDED
