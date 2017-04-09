#pragma once

#include "../equipment.h"
//#include "../../hero.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			class Weapon : public Equipment
			{
			private:

			public:
				Weapon() noexcept;
				~Weapon() noexcept;
				//Weapon(int amount) : Equipment(amount) {};

				void SetName();
				void SetDescription();
				void Equip(Hero* h);
				void UnEquip(Hero* h);
			};
			std::vector<game::items::equipment::Weapon*> GetWeapons();
		}
	}
}
