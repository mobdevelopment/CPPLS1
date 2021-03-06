#ifndef _GAME_ITEMS_ITEM_H_
#define _GAME_ITEMS_ITEM_H_

#include <string>
#include <vector>
#include <unordered_map>

//#include "../hero.h"

namespace game { 
	
	namespace items {
		class Item;
		class Consumable;
		class Equipment;
	}

	class Hero;

	namespace items {

		/*typedef std::unordered_map<int, Item> ItemsContainer;*/

		class Item
		{
		private:

		public:
			std::string	name;
			std::string description;
			std::string iType;

			Item() noexcept;
			virtual ~Item() noexcept;

			virtual void SetName();
			virtual void SetDescription();
			virtual void SetIType();

			virtual void Use(Hero& h);
		};

		class SaveItem
		{
		public:
			std::string name;
			int			x;
			int			y;
			int			z;
			unsigned int			amount = 0;
		};


		//std::vector<game::items::Item*> encounterableItems;
		std::vector<game::items::Item*> GetSavedItems();
	}
}

#endif // _GAME_ITEMS_ITEM_H_