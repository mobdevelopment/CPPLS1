#pragma once
#include "../shoes.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			namespace shoes {

				class LeatherShoes : public Shoes
				{
				private:

				public:
					LeatherShoes() noexcept;
					~LeatherShoes() noexcept;

					void SetName();
					void SetDescription();
					void SetIType();

					int GetEffect();

					void Use(Hero& h);

				};
			}
		}
	}
}