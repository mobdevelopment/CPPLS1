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

				virtual void SetName();
				virtual void SetDescription();
				virtual void SetIType();

				void Use(Hero* h);
			};
			std::vector<game::items::equipment::Shield*> GetShields();
		}
	}
}
