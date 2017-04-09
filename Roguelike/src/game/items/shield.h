#pragma once
#include "item.h"
#include "useable.h"

namespace game
{
	namespace items
	{
		class Shield : public Useable
		{
		private:

		public:
			Shield() noexcept;
			~Shield() noexcept;
			Shield(int amount) : Useable(amount) {};
			int limit = 1;

			void SetName();
			void SetEffect();
			void Use(Hero* h);
		};
	}

}
