#include "userinterface.h"

using namespace ui::cnsl;

void UserInterface::ExitCommandHandler(utils::cmd::Command& command)
{
	shouldExit = true;
}

void UserInterface::BackCommandHandler(utils::cmd::Command& command)
{
	GoToPreviousState();
}

UserInterface::UserInterface(game::Game& game) noexcept :
	UserInterface(game, std::cin)
{
}

UserInterface::UserInterface(game::Game& game, std::istream& inputStream) noexcept :
	UserInterfaceBase(game),
	inputStream(inputStream),
	stateContext(*this, game)
{
}

UserInterface::~UserInterface() noexcept
{
	// Delete the states.
	for (auto* const state: states)
		delete state;
}

void UserInterface::Start()
{
	// Register the global commands.
	RegisterCommand<>("Exit", std::bind(&UserInterface::ExitCommandHandler, this, std::placeholders::_1));
	RegisterCommand<>("Back", std::bind(&UserInterface::BackCommandHandler, this, std::placeholders::_1));

	// Add the first default state and initalize it.
	states.push_back(state::Factory::GetInstance().ConstructDefaultState(stateContext));
	GetState()->Initialize();

	// Initial drawing of the console.
	DrawConsole();

	// Loop through the incoming console commands.
	while (!shouldExit)
	{
		std::error_code errorBuffer;
		utils::cmd::Command command = ParseCommand(inputStream, errorBuffer);
		HandleCommand(command, errorBuffer);

		if (errorBuffer == utils::cmd::Error::COMMAND_NOT_REGISTERED)
		{
			DrawConsole("Invalid command: '" + command.command + "'.");
		}
		else if (errorBuffer)
		{
			DrawConsole("Something went wrong parsing your command. Please try again.");
		}
	}
}

state::BaseInterface* UserInterface::GetState() const noexcept
{
	if (states.empty())
		return nullptr;
	return states.back();
}

void UserInterface::SetState(const state::Type type)
{
	// Terminate the current state.
	GetState()->Terminate();

	// Put the state into the stack so we can go back to it.
	states.push_back(state::Factory::GetInstance().Construct(type, stateContext));

	// Initialize the new state.
	GetState()->Initialize();

	// And redraw.
	DrawConsole();
}

void UserInterface::GoToPreviousState()
{
	if (states.size() <= 1)
	{
		DrawConsole("There is no previous screen to go back to.");
		return;
	}

	delete states.back();
	states.pop_back();

	// Initialize the state.
	GetState()->Initialize();

	// And redraw.
	DrawConsole();
}

void UserInterface::ClearConsole() const noexcept
{
#ifdef _WIN32
	system("cls");
#elif
	for (int i = 0; i < 50; i++)
	{
		std::cout << std::endl;
	}
#endif // _WIN32
}

void UserInterface::DrawConsole() const
{
	ClearConsole();
	if (GetState() != nullptr)
		GetState()->DrawConsole();

	std::cout << std::endl << std::endl << "The following commands are available:";

	for (const auto& command: GetAvailableCommands())
	{
		std::cout << std::endl << command.command;

		for (auto& parameter: command.parameters)
		{
			std::cout << " <" << parameter << '>';
		}

		std::cout << " - " << command.description;
	}

	std::cout << std::endl << std::endl;
}

void UserInterface::DrawConsole(const std::string extraMessage) const
{
	DrawConsole();

	std::cout << extraMessage << std::endl << std::endl;
}

std::vector<CommandDescription> UserInterface::GetAvailableCommands() const
{
	std::vector<CommandDescription> commandDescriptions;
	if (GetState() != nullptr)
		GetState()->GetAvailableCommands(commandDescriptions);

	CommandDescription backCommandDescription;
	backCommandDescription.command = "Back";
	backCommandDescription.description = "Go to the previous screen.";

	CommandDescription exitCommandDescription;
	exitCommandDescription.command = "Exit";
	exitCommandDescription.description = "Exit the game.";

	commandDescriptions.emplace_back(std::move(backCommandDescription));
	commandDescriptions.emplace_back(std::move(exitCommandDescription));

	return commandDescriptions;
}
