#pragma once

#include "../equipment.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			class Shoes : public Equipment
			{
			private:

			public:
				Shoes() noexcept;
				~Shoes() noexcept;

				virtual void SetName();
				virtual void SetDescription();
				virtual void SetIType();

				void Use(Hero& h);
				int GetEffect();
			};
			std::vector<game::items::equipment::Shoes*> GetShoes();
		}
	}
}
