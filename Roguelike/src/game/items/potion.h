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

			void Use();
		};
	}

}
