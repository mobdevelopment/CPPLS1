#pragma once
#include <string>
#include <vector>
#include <unordered_map>

//#include "../hero.h"
#include "item.h"

namespace game {

	//class Hero;

	namespace items {

		class Consumable : public Item
		{
		private:

		public:
			Consumable() noexcept;
			~Consumable() noexcept;
			Consumable(int amount) noexcept;

			virtual void SetName();
			virtual void SetDescription();
			virtual void SetIType();

			virtual void Use(Hero* h);
		};
		std::vector<game::items::Consumable*> GetConsumables();
	}
}