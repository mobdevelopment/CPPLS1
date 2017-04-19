#ifndef UI_CNSL_STATE_SAVESELECTION_HEADER_INCLUDED
#define UI_CNSL_STATE_SAVESELECTION_HEADER_INCLUDED

#include <iostream>
#include <vector>

#include "../../../game/save.h"

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
			class SaveSelection :
				public Base<SaveSelection>
			{
			private:
				game::SavesContainer saves;

				void SelectCommandHandler(utils::cmd::Command& command);

			public:
				static const Type TYPE;

				using Base::Base;

				void Initialize() override;
				void Terminate() override;

				void DrawConsole() const override;
				void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
			}; // class SaveSelection
		} // namespace ui
	} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_SAVESELECTION_HEADER_INCLUDED
