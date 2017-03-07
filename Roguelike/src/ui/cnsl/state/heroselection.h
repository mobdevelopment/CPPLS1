#ifndef UI_CNSL_STATE_HEROSELECTION_HEADER_INCLUDED
#define UI_CNSL_STATE_HEROSELECTION_HEADER_INCLUDED

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
	class HeroSelection :
		public Base<HeroSelection>
	{
	private:
		game::HeroesContainer heroes;

		void SelectCommandHandler(utils::cmd::Command& command);

	public:
		static const Type TYPE;

		using Base::Base;

		void Initialize() override;
		void Terminate() override;

		void DrawConsole() const override;
		void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
	}; // class HeroSelection
} // namespace ui
} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_HEROSELECTION_HEADER_INCLUDED
