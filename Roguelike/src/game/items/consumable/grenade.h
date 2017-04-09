#pragma once
//#include "item.h"
#include "../consumable.h"

namespace game
{
	namespace items
	{
		namespace consumable {

			class Grenade : public Consumable
			{
			private:

			public:
				Grenade() noexcept;
				~Grenade() noexcept;

				void Use();
			};
		}
	}

}
