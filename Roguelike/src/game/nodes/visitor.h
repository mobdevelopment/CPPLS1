#ifndef GAME_NODES_VISITOR_HEADER_INCLUDED
#define GAME_NODES_VISITOR_HEADER_INCLUDED

namespace game
{
namespace nodes
{
	class Room;
	class StairsDown;
	class StairsUp;
	class HorizontalCorridor;
	class VerticalCorridor;

	class Visitor
	{
	public:
		virtual ~Visitor() noexcept = 0;

		virtual void Visit(Room& node) = 0;
		virtual void Visit(StairsDown& node) = 0;
		virtual void Visit(StairsUp& node) = 0;
		virtual void Visit(HorizontalCorridor& node) = 0;
		virtual void Visit(VerticalCorridor& node) = 0;
	}; // class Visitor
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_VISITOR_HEADER_INCLUDED
