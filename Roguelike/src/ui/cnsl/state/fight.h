#ifndef UI_CNSL_STATE_FIGHT_HEADER_INCLUDED
#define UI_CNSL_STATE_FIGHT_HEADER_INCLUDED

#include <iostream>
#include <vector>
#include <numeric>

#include "../../../game/hero.h"
#include "../../../game/nodes/room.h"

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
			class Fight :
				public Base<Fight>
			{
			private:
				void FightCommandHandler(utils::cmd::Command& command);
				std::vector<std::string> AttackByEnemy();
				std::vector<std::string> AttackByHero();
			public:
				static const Type TYPE;

				using Base::Base;

				void Initialize() override;
				void Terminate() override;

				void DrawConsole() const override;
				void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
			};
		} // namespace ui
	} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_FIGHT_HEADER_INCLUDED
