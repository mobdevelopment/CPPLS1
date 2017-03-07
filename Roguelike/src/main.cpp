#include "main.h"

void ShowErrorMessage(const char* const message)
{
#ifdef _WIN32
	if (message != nullptr)
		MessageBoxA(nullptr, message, "Error!", MB_ICONERROR);
	else
		MessageBoxA(nullptr, "A fatal error occurred.", "Error!", MB_ICONERROR);
#endif // _WIN32
}

void Initialize()
{
	game::Game game;
	ui::UserInterfaceBase* userInterface = new ui::cnsl::UserInterface(game);

	try
	{
		userInterface->Start();
	}
	catch (...)
	{
		delete userInterface;
		throw;
	}

	delete userInterface;
}

int main()
{
	// Return 0 by default for no error.
	int returnValue = 0;

#ifdef _DEBUG
 #ifdef _WIN32
	// Initialize memory leak detection.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
 #endif // _WIN32
	Initialize();
#else
	try
	{
		Initialize();
	}
	catch (std::system_error& exception)
	{
		ShowErrorMessage(exception.code().message().c_str());

		// Return the error code.
		returnValue = exception.code().value();
	}
	catch (std::exception& exception)
	{
		ShowErrorMessage(exception.what());

		// Return -1 indicating an error occurred.
		returnValue = -1;
	}
	catch (...)
	{
		ShowErrorMessage(nullptr);

		// Return -1 indicating an error occurred.
		returnValue = -1;
	}
#endif

	return returnValue;
}
