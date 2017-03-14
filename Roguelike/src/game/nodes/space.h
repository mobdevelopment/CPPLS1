#ifndef GAME_NODES_SPACE_HEADER_INCLUDED
#define GAME_NODES_SPACE_HEADER_INCLUDED

#include <vector>
#include <sstream>
#include <string>

#include "node.h"
#include "type.h"

#include "corridor.h"
#include "verticalcorridor.h"
#include "horizontalcorridor.h"

namespace game
{
	namespace nodes
	{
		class Corridor;
		class HorizontalCorridor;
		class VerticalCorridor;

		class Space
		{
		public:
			VerticalCorridor*	northCorridor;
			HorizontalCorridor*	eastCorridor;
			VerticalCorridor*	southCorridor;
			HorizontalCorridor*	westCorridor;

			virtual unsigned int GetWeight() const = 0;

			std::vector<Corridor*> GetConnectedCorridors() const;
			std::vector<Space*> GetConnectedRooms() const;

			virtual std::string GetDescription() const = 0;
		};
	} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_SPACE_HEADER_INCLUDED
