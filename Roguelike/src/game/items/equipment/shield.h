#pragma once
//#include "item.h"
#include "../equipment.h"

//#include "../../hero.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			class Shield : public Equipment
			{
			private:

			public:
				Shield() noexcept;
				~Shield() noexcept;
				Shield(int amount) : Equipment(amount) {};
				int limit = 1;

				void SetName();
				void SetDescription();
				void Use(Hero* h);
			};
			std::vector<game::items::equipment::Shield*> GetShields();
		}
	}
}
