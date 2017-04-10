#pragma once
//#include "item.h"
#include "../consumable.h"

namespace game
{
	namespace items
	{
		namespace consumable {

			class Talisman : public Consumable
			{
			private:

			public:
				Talisman() noexcept;
				~Talisman() noexcept;
				//Talisman(int amount) : Item(amount) {};
				Talisman(int amount) : Consumable(amount) {};

				void SetName();
				void SetDescription();
				void SetIType();

				void Use(Hero& h);
			};
		}
	}

}
