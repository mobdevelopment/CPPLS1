#ifndef _GAME_ITEMS_ITEM_H_
#define _GAME_ITEMS_ITEM_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "../hero.h"


namespace game { 
	
	class Hero;

	namespace items {
	
		class Item;

		/*typedef std::unordered_map<int, Item> ItemsContainer;*/

		class Item
		{
		private:

		public:
			std::string	name;
			std::string description;
			int amount = 0;
			int limit = -1;

			Item() noexcept;
			~Item() noexcept;
			Item(int amount) noexcept;
			virtual void SetName();
			virtual void SetDescription();

			virtual void Use(Hero* h);
		};

		//std::vector<game::items::Item*> encounterableItems;
		std::vector<game::items::Item*> GetSavedItems();
	}
}

#endif // _GAME_ITEMS_ITEM_H_