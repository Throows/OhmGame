#include <iostream>
#include <OhmEngine/OhmEngine.hpp>

int main(int argc, char** argv) 
{
	OHE::Logger::Init();

	OHE_GAME_INFO("Starting game !");
	OHE::Application app(argc, argv);
	OHE_GAME_INFO("Game Started !");

	return app.Run();
}