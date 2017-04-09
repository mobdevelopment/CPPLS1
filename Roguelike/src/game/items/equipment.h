#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "item.h"
//#include "../hero.h"

namespace game {

	//class Hero;

	namespace items {

		class Equipment : public Item
		{
		private:

		public:
			int lifePoints = 0;
			int attackAmount = 1;
			int attackChance = 0;
			int defenceChance = 0;
			int minDamage = 0;
			int maxDamage = 0;

			Equipment() noexcept;
			~Equipment() noexcept;

			virtual void SetName();
			virtual void SetDescription();

			virtual void Equip(Hero* h);
			virtual void UnEquip(Hero* h);
		};
		std::vector<game::items::Equipment*> GetEquipments();
	}
}