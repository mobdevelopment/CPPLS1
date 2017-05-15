#ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED
#define UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED

#include <vector>
#include <string>

namespace ui
{
namespace cnsl
{
	class CommandDescription
	{
	public:
		std::string command;
		std::string description;
		std::vector<std::string> parameters;
	}; // class CommandDescription
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_COMMANDDESCRIPTION_HEADER_INCLUDED
