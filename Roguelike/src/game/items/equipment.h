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
			Equipment() noexcept;
			~Equipment() noexcept;
			Equipment(int amount) : Item(amount) {};

			int lifePoints = 0;
			int attackAmount = 1;
			int attackChance = 0;
			int defenceChance = 0;
			int minDamage = 0;
			int maxDamage = 0;

			virtual void SetName();
			virtual void SetDescription();
			virtual void SetIType();

			virtual void Use(Hero* h);
		};
		std::vector<game::items::Equipment*> GetEquipments();
	}
}