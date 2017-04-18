#ifndef GAME_DUNGEONLAYER_HEADER_INCLUDED
#define GAME_DUNGEONLAYER_HEADER_INCLUDED

#include <vector>
#include <unordered_set>
#include <random>

#include "dungeonrow.h"

#include "nodes/room.h"
#include "nodes/corridor.h"

namespace game
{
	class DungeonLayer
	{
	public:
		typedef std::vector<DungeonRow>					RowsContainer;

		typedef typename RowsContainer::iterator		iterator;
		typedef typename RowsContainer::const_iterator	const_iterator;

	private:
		unsigned int	width;
		unsigned int	height;

		RowsContainer	rows;

	public:
		DungeonLayer() noexcept;

		iterator begin();
		const_iterator begin() const;
		const_iterator cbegin() const;
		iterator end();
		const_iterator end() const;
		const_iterator cend() const;

		DungeonRow& operator[](const unsigned int index) noexcept;
		const DungeonRow& operator[](const unsigned int index) const noexcept;

		unsigned int GetWidth() const noexcept;
		unsigned int GetHeight() const noexcept;
		unsigned int GetSurfaceArea() const noexcept;

		RowsContainer& GetRows() noexcept;
		const RowsContainer& GetRows() const noexcept;

		nodes::Room* GetRandomRoom(const int seed) const noexcept;

		void SetWidth(const unsigned int width);
		void SetHeight(const unsigned int height);

		bool IsEverythingAccessible(const int seed) const;

		std::vector<nodes::Corridor*> GetMinimalSpanningTree(const int seed) const;
	}; // class DungeonLayer
} // namespace game

#endif // #ifndef GAME_DUNGEONLAYER_HEADER_INCLUDED
