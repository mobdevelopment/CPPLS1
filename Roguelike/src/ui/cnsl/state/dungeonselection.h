#ifndef UI_CNSL_STATE_DUNGEONSELECTION_HEADER_INCLUDED
#define UI_CNSL_STATE_DUNGEONSELECTION_HEADER_INCLUDED

#include <iostream>
#include <vector>
#include <random>

#include <utils/cmd/command.hpp>

#include "../../../game/dungeon.h"

#include "../commanddescription.h"
#include "../userinterface.h"

#include "base.h"
#include "type.h"

namespace ui
{
namespace cnsl
{
namespace state
{
	class DungeonSelection :
		public Base<DungeonSelection>
	{
	private:
		void StartCommandHandler(utils::cmd::Command& command);
		void SetDungeonValueCommandHandler(utils::cmd::Command& command, unsigned int* const value);

		unsigned int dungeonLayers;
		unsigned int dungeonWidth;
		unsigned int dungeonHeight;
		unsigned int dungeonSeed;

	public:
		static const Type TYPE;

		using Base::Base;

		void Initialize() override;
		void Terminate() override;

		void DrawConsole() const override;
		void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
	}; // class DungeonSelection
} // namespace ui
} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_DUNGEONSELECTION_HEADER_INCLUDED
