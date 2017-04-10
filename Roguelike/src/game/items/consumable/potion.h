#pragma once
//#include "item.h"
#include "../consumable.h"

namespace game
{
	namespace items
	{
		namespace consumable {

			class Potion : public virtual Consumable
			{
			private:

			public:
				Potion() noexcept;
				~Potion() noexcept;
				//Potion(int amount) : Item(amount) {};
				Potion(int amount) : Consumable(amount) {};

				void SetName();
				void SetDescription();
				void SetIType();

				void Use(Hero* h);

				void ImAConsumable();
			};
		}
	}

}
