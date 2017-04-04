#ifndef _GAME_ITEMS_ITEM_H_
#define _GAME_ITEMS_ITEM_H_

#include "../hero.h"


namespace game { 
	
	class Hero;

	namespace items {
	

		class Item
		{
		private:

		public:
			int amount;

			Item() noexcept;
			~Item() noexcept;

			virtual void Use(Hero* h);
		};
	}
}

#endif // _GAME_ITEMS_ITEM_H_