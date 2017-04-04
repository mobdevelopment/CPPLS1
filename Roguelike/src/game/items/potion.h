#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class Potion : public Item
		{
		private:

		public:
			Potion() noexcept;
			~Potion() noexcept;
			Potion(int amount) : Item(amount) {};

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
