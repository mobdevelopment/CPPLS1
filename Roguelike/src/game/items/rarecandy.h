#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class RareCandy : public Item
		{
		private:

		public:
			RareCandy() noexcept;
			~RareCandy() noexcept;
			RareCandy(int amount) : Item(amount) {};

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
#pragma once
