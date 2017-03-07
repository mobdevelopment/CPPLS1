#ifndef UI_USERINTERFACEBASE_HEADER_INCLUDED
#define UI_USERINTERFACEBASE_HEADER_INCLUDED

namespace game
{
	class Game;
} // namespace game

namespace ui
{
	class UserInterfaceBase
	{
	protected:
		game::Game& game;

	public:
		UserInterfaceBase(game::Game& game) noexcept;
		virtual ~UserInterfaceBase() noexcept = 0;

		virtual void Start() = 0;
	}; // class UserInterfaceBase
} // namespace ui

#endif // #ifndef UI_USERINTERFACEBASE_HEADER_INCLUDED
