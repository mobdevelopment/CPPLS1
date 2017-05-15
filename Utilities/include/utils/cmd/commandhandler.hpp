#ifndef UTILS_CMD_COMMANDHANDLER_HEADER_INCLUDED
#define UTILS_CMD_COMMANDHANDLER_HEADER_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <algorithm>

#include <boost/noncopyable.hpp>

#include "errorcategory.h"
#include "command.hpp"

namespace
{
	void CheckStreamValidity(const std::istream& stream);
} // namespace

namespace utils
{
namespace cmd
{
	namespace detail
	{
		class CommandParametersParserBase
		{
		public:
			virtual void Parse(std::istream& stream, Command& command) const = 0;
		};

		template <typename ...Parameters>
		class CommandParametersParser :
			public CommandParametersParserBase
		{
			void Parse(std::istream& stream, Command& command) const override
			{
				detail::ParseCommandParameters<Parameters...>(stream, command);
			}
		};
	} // namespace detail

	class CommandHandler
	{
		typedef std::function<void(Command&)> CommandCallback;
		typedef std::unordered_map<std::string, std::pair<const detail::CommandParametersParserBase* const, const CommandCallback>> CommandHandlersContainer;

	private:
		CommandHandlersContainer commandHandlers;

	public:
		~CommandHandler() noexcept
		{
			for (auto& commandHandle : commandHandlers)
			{
				delete commandHandle.second.first;
			}
		}

		template <typename ...Parameters>
		void RegisterCommand(std::string commandName, CommandCallback commandCallback)
		{
			std::transform(commandName.begin(), commandName.end(), commandName.begin(), tolower);
			commandHandlers.emplace(commandName, std::make_pair(new detail::CommandParametersParser<Parameters...>, commandCallback));
		}

		void UnregisterCommand(std::string commandName)
		{
			std::transform(commandName.begin(), commandName.end(), commandName.begin(), tolower);

			auto commandHandler = commandHandlers.find(commandName);
			if (commandHandler == commandHandlers.end())
				throw std::system_error(Error::COMMAND_NOT_REGISTERED);

			delete commandHandlers.at(commandName).first;
			commandHandlers.erase(commandName);
		}

		Command ParseCommand(std::istream& stream) const
		{
			Command command;

			// Parse the incoming command to a string stream buffer.
			std::stringstream streamBuffer;
			std::string line;
			std::getline(stream, line);
			CheckStreamValidity(stream);

			streamBuffer << line;

			std::getline(streamBuffer, command.command, ' ');
			CheckStreamValidity(stream);
			std::transform(command.command.begin(), command.command.end(), command.command.begin(), tolower);

			// Check if the command is registered.
			auto commandHandler = commandHandlers.find(command.command);
			if (commandHandler == commandHandlers.end())
				throw std::system_error(Error::COMMAND_NOT_REGISTERED);

			// Parse the command parameters.
			commandHandler->second.first->Parse(streamBuffer, command);

			return command;
		}

		Command ParseCommand(std::istream& stream, std::error_code& errorBuffer) const
		{
			try
			{
				return ParseCommand(stream);
			}
			catch (std::system_error exception)
			{
				errorBuffer = exception.code();
			}
		}

		void HandleCommand(Command& command) const
		{
			// Check if the command is registered.
			auto commandHandler = commandHandlers.find(command.command);
			if (commandHandler == commandHandlers.end())
				throw std::system_error(Error::COMMAND_NOT_REGISTERED);

			// Call the command handler callback.
			commandHandler->second.second(command);
		}

		void HandleCommand(Command& command, std::error_code& errorBuffer) const
		{
			try
			{
				HandleCommand(command);
			}
			catch (std::system_error exception)
			{
				errorBuffer = exception.code();
			}
		}
	}; // class CommandHandler
} // namespace cmd
} // namespace utils

#endif // #ifndef UTILS_CMD_COMMANDHANDLER_HEADER_INCLUDED
