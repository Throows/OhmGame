#include <iostream>
#include <OhmEngine/OhmEngine.hpp>

int main(int argc, char** argv) 
{
	OHE::Logger::Init();

	OHE_GAME_INFO("Starting game !");
	OHE::Application app(argc, argv);
	app.InitializeApplication();
	app.Run();
	OHE_GAME_INFO("Game Started !");
	app.Cleanup();
	OHE_GAME_INFO("Game Cleaned Up !");
	return 0;
}