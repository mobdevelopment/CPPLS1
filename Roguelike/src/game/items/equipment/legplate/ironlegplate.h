#pragma once
#include "../legplate.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			namespace legplate {

				class IronLegplate : public Legplate
				{
				private:

				public:
					IronLegplate() noexcept;
					~IronLegplate() noexcept;

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