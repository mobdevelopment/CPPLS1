#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class Weapon : public Item
		{
		private:

		public:
			Weapon() noexcept;
			~Weapon() noexcept;
			Weapon(int amount) : Item(amount) {};

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
