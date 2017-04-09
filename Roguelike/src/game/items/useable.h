#ifndef _GAME_ITEMS_USEABLE_H_
#define _GAME_ITEMS_USEABLE_H_

#include <string>
#include <vector>
#include <unordered_map>

#include "../hero.h"
#include "item.h"


namespace game {

	class Hero;

	namespace items {

		class Useable : public Item
		{
		private:

		public:
			Useable() noexcept;
			~Useable() noexcept;
			Useable(int amount) : Item(amount) {};

			void Use(Hero* h) = 0;
		};
	}
}

#endif // _GAME_ITEMS_USEABLE_H_