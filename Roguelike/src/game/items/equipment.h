#ifndef _GAME_ITEMS_EQUIPMENT_H_
#define _GAME_ITEMS_EQUIPMENT_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "item.h"
#include "../hero.h"

namespace game {

	class Hero;

	namespace items {

		class Item;
		class Consumable;

		class Equipment : public Item
		{
		private:

		public:
			Equipment() noexcept;
			~Equipment() noexcept;

			int lifePoints = 0;
			int attackAmount = 1;
			int attackChance = 0;
			int defenceChance = 0;
			int minDamage = 0;
			int maxDamage = 0;

			virtual void ImAEquipable();
		};
		std::vector<game::items::Equipment*> GetEquipments();
	}
}

#endif // _GAME_ITEMS_EQUIPMENT_H_