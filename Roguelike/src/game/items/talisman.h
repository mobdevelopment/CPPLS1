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

			void Use();
		};
	}

}
