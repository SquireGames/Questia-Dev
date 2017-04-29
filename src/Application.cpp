#include "QuestiaDev/Application.h"

Application::Application():
	eng("Questia", 500)
{
	std::cout << "--------------------" << std::endl;
	std::cout << "  Questia Executed  " << std::endl;
	std::cout << "--------------------" << std::endl;

	eng.state().reg("MainMenu", []() {return new State_MainMenu();});
	eng.state().reg("Game",     []() {return new State_Game();});
	eng.state().reg("Loading",  []() {return new State_Loading();});
	
	eng.state().transitionState("MainMenu", "Loading");
	
	eng.guiLd().setGuiPack("Default");
}

Application::~Application()
{
	std::cout << "--------------------" << std::endl;
	std::cout << " Questia Terminated " << std::endl;
	std::cout << "--------------------" << std::endl;
}


void Application::run()
{
	//while the application is still running
	while(eng.run())
	{
		//while the application is due to update
		while(eng.tick())
		{
			eng.processInput();
			eng.state().sUpdate();
		}

		//render when possible, but only to the framerate limit
		eng.state().sDisplay();
		eng.render();
	}
}
