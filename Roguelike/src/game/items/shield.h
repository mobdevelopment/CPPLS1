#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class Shield : public Item
		{
		private:

		public:
			Shield() noexcept;
			~Shield() noexcept;
			Shield(int amount) : Item(amount) {};
			int limit = 1;

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
