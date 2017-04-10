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

				virtual void SetName();
				virtual void SetDescription();
				virtual void SetIType();

				void Use(Hero* h);
			};
			std::vector<game::items::equipment::Weapon*> GetWeapons();
		}
	}
}
