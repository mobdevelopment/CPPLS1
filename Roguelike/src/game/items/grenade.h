#pragma once
#include "item.h"

namespace game
{
	namespace items
	{
		class Grenade : public Item
		{
		private:

		public:
			Grenade() noexcept;
			~Grenade() noexcept;

			void Use();
		};
	}

}
