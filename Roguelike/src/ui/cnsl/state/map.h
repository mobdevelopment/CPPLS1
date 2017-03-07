#ifndef UI_CNSL_STATE_MAP_HEADER_INCLUDED
#define UI_CNSL_STATE_MAP_HEADER_INCLUDED

#include <iostream>
#include <vector>

#include <utils/cmd/command.hpp>

#include "../../../game/dungeon.h"

#include "../../../game/nodes/type.h"

#include "../commanddescription.h"

#include "base.h"
#include "type.h"

namespace ui
{
namespace cnsl
{
namespace state
{
	class Map :
		public Base<Map>
	{
	public:
		static const Type TYPE;

		using Base::Base;

		void Initialize() override;
		void Terminate() override;

		void DrawConsole() const override;
		void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
	}; // class Map
} // namespace ui
} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_MAP_HEADER_INCLUDED
