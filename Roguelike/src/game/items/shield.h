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

			void Use();
		};
	}

}
