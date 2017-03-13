#ifndef GAME_DUNGEON_HEADER_INCLUDED
#define GAME_DUNGEON_HEADER_INCLUDED

#include <iostream>
#include <vector>
#include <random>
#include <queue>
#include <stack>
#include <unordered_set>

#include "error.h"
#include "errorcategory.h"
#include "dungeonlayer.h"

#include "nodes/node.h"
#include "nodes/room.h"
#include "nodes/stairsdown.h"
#include "nodes/stairsup.h"
#include "nodes/horizontalcorridor.h"
#include "nodes/verticalcorridor.h"

namespace game
{
	class Dungeon
	{
	public:
		typedef std::vector<DungeonLayer>					LayersContainer;

		typedef typename LayersContainer::iterator			iterator;
		typedef typename LayersContainer::const_iterator	const_iterator;

	private:
		LayersContainer	layers;

		unsigned int	seed;
		unsigned int	layerCount;

		unsigned int	roomsWidth;
		unsigned int	roomsHeight;

	public:
		Dungeon() noexcept;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		DungeonLayer& operator[](const unsigned int index) noexcept;
		const DungeonLayer& operator[](const unsigned int index) const noexcept;

		void Clear() noexcept;

		void Fill(const unsigned int layerCount, const unsigned int width, const unsigned int height);
		void Randomize(const unsigned int layerCount, const unsigned int width, const unsigned int height);
		void Randomize(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed);

		void BFS(nodes::Room room);

		LayersContainer& GetLayers() noexcept;
		const LayersContainer& GetLayers() const noexcept;

		unsigned int GetRoomsWidth() const;
		unsigned int GetRoomsHeight() const;
		unsigned int GetTotalWidth() const;
		unsigned int GetTotalHeight() const;
	}; // class Dungeon
} // namespace game

#endif // #ifndef GAME_DUNGEON_HEADER_INCLUDED
