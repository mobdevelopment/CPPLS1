#include "map.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Map::TYPE(Type::MAP);

void Map::Initialize()
{
}

void Map::Terminate()
{
}

void Map::DrawConsole() const
{
	std::cout << "Map" << std::endl << std::endl;

	for (const auto& dungeonRow : context.game.GetDungeon().GetLayers()[0])
	{
		for (const auto* const node : dungeonRow.GetNodes())
		{
			if (node == nullptr)
			{
				std::cout << ' ';
				continue;
			}

			auto type = node->GetType();

			if (node == static_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
			{
				std::cout << 'C';
			}
			else
			{
				switch (type)
				{
				case game::nodes::Type::ROOM:
					std::cout << 'N';
					break;
				case game::nodes::Type::STAIRS_DOWN:
					std::cout << 'D';
					break;
				case game::nodes::Type::STAIRS_UP:
					std::cout << 'U';
					break;
				case game::nodes::Type::HORIZONTAL_CORRIDOR:
					std::cout << '-';
					break;
				case game::nodes::Type::VERTICAL_CORRIDOR:
					std::cout << '|';
					break;
				}
			}

			
		}

		std::cout << std::endl;
	}
}

void Map::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
}