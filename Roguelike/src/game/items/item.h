#ifndef _GAME_ITEMS_ITEM_H_
#define _GAME_ITEMS_ITEM_H_


namespace game { namespace items
{
	class Item
	{
		private:

		public:
			Item() noexcept;
			~Item() noexcept;

			virtual void Use() = 0;
	};
}}

#endif // _GAME_ITEMS_ITEM_H_