#ifndef _GAME_ITEMS_CONSUMABLE_H_
#define _GAME_ITEMS_CONSUMABLE_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "item.h"
#include "../hero.h"

namespace game {

	class Hero;

	namespace items {

		class Item;
		class Equipment;

		class Consumable : public Item
		{
		private:

		public:
			int amount = 0;

			Consumable() noexcept;
			~Consumable() noexcept;
			Consumable(int amount) noexcept;

			virtual void ImAConsumable();
		};

		std::vector<game::items::Consumable*> GetConsumables();
	}
}

#endif // _GAME_ITEMS_CONSUMABLE_H_