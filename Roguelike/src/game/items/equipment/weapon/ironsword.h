#pragma once
#include "../weapon.h"

namespace game
{
	namespace items
	{
		namespace equipment {
			
			namespace weapon {

				class IronSword : public Weapon
				{
				private:

				public:
					IronSword() noexcept;
					~IronSword() noexcept;

					void SetName();
					void SetDescription();
					void Equip(Hero* h);
					void UnEquip(Hero* h);
				};
			}
		}
	}
}