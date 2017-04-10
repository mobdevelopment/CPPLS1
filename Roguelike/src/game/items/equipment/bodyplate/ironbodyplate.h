#pragma once
#include "../bodyplate.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			namespace bodyplate {

				class IronBodyplate : public Bodyplate
				{
				private:

				public:
					IronBodyplate() noexcept;
					~IronBodyplate() noexcept;

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