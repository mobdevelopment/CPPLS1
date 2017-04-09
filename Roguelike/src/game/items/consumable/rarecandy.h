#pragma once
//#include "item.h"
#include "../consumable.h"

namespace game
{
	namespace items
	{
		namespace consumable {

			class RareCandy : public Consumable
			{
			private:

			public:
				RareCandy() noexcept;
				~RareCandy() noexcept;
				//RareCandy(int amount) : Item(amount) {};
				RareCandy(int amount) : Consumable(amount) {};
	
				void SetName();
				void SetDescription();
				void Use(Hero* h);
			};
		}
	}

}
#pragma once
