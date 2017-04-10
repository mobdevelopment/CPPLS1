#pragma once
#include "../shield.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			namespace shield {

				class IronShield : public Shield
				{
				private:

				public:
					IronShield() noexcept;
					~IronShield() noexcept;

					void SetName();
					void SetDescription();
					void SetIType();

					void Use(Hero* h);
				};
			}
		}
	}
}
