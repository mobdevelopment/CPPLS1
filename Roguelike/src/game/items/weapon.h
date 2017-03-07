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

			void Use();
		};
	}

}
