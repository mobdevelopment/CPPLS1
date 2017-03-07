#ifndef UI_CNSL_STATE_MENU_HEADER_INCLUDED
#define UI_CNSL_STATE_MENU_HEADER_INCLUDED

#include <iostream>
#include <vector>

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
	class Menu :
		public Base<Menu>
	{
	public:
		static const Type TYPE;

		using Base::Base;

		void Initialize() override;
		void Terminate() override;

		void DrawConsole() const override;
		void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const override;
	}; // class Menu
} // namespace ui
} // namespace cnsl
} // namespace state

#endif // #ifndef UI_CNSL_STATE_MENU_HEADER_INCLUDED
