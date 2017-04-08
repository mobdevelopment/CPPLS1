#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class Talisman : public Item
		{
		private:

		public:
			Talisman() noexcept;
			~Talisman() noexcept;
			Talisman(int amount) : Item(amount) {};

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
