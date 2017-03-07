#ifndef UI_CNSL_STATE_HEROCREATION_HEADER_INCLUDED
#define UI_CNSL_STATE_HEROCREATION_HEADER_INCLUDED

#include <iostream>
#include <vector>

#include "../../../game/hero.h"

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
	class HeroCreation :
		public Base<HeroCreation>
	{
	private:
		game::Hero hero;

		void NameCommandHandler(utils::cmd::Command& command);
		void RandomNameCommandHandler(utils::cmd::Command& command);
		void SaveCommandHandler(utils::cmd::Command& command);

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

#endif // #ifndef UI_CNSL_STATE_HEROCREATION_HEADER_INCLUDED
