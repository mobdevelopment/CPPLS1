#ifndef GAME_DUNGEONROW_HEADER_INCLUDED
#define GAME_DUNGEONROW_HEADER_INCLUDED

#include <vector>

#include <boost/noncopyable.hpp>

#include "nodes/node.h"
#include "nodes/type.h"
#include "nodes/room.h"

namespace game
{
	class DungeonRow
	{
	public:
		typedef std::vector<nodes::NodeInterface*>	NodesContainer;
		typedef std::vector<nodes::Room*>			RoomsContainer;

		typedef typename NodesContainer::iterator		iterator;
		typedef typename NodesContainer::const_iterator	const_iterator;

	private:
		unsigned int	width;

		NodesContainer	nodes;

	public:
		DungeonRow() noexcept;
		~DungeonRow() noexcept;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		nodes::NodeInterface* operator[](const unsigned int index) noexcept;
		const nodes::NodeInterface* operator[](const unsigned int index) const noexcept;

		unsigned int GetWidth() const noexcept;
		void SetWidth(const unsigned int width);

		NodesContainer& GetNodes() noexcept;
		const NodesContainer& GetNodes() const noexcept;

		RoomsContainer GetRooms() const noexcept;

		void SetNode(const unsigned int index, nodes::NodeInterface* node) noexcept;
	}; // class DungeonRow
} // namespace game

#endif // #ifndef GAME_DUNGEONROW_HEADER_INCLUDED
