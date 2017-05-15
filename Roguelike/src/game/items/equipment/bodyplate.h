#pragma once

#include "../equipment.h"

namespace game
{
	namespace items
	{
		namespace equipment {

			class Bodyplate : public Equipment
			{
			private:

			public:
				Bodyplate() noexcept;
				~Bodyplate() noexcept;

				virtual void SetName();
				virtual void SetDescription();
				virtual void SetIType();

				void Use(Hero& h);
				int GetEffect();
			};
			std::vector<game::items::equipment::Bodyplate*> GetBodyplates();
		}
	}
}
