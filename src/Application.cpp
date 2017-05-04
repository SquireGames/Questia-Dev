#include "QuestiaDev/Application.h"

Application::Application():
	eng("", 128)
{
	//enforce windowed mode
	eng.win().create(sf::VideoMode(1920, 1080), "Questia Editor", sf::Style::Default);
	eng.win().setVerticalSyncEnabled(true);;
	
	eng.state().reg("MainMenu", 	[]() {return new State_MainMenu();});
	eng.state().reg("OptionsMenu",  []() {return new State_OptionsMenu();});
	eng.state().reg("MapEditor",    []() {return new State_MapEditor();});
	eng.state().reg("Loading",  	[]() {return new State_Loading();});
	
	eng.state().transitionState("MainMenu", "Loading");
	
	eng.guiLd().setGuiPack("Default");
}

Application::~Application()
{

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
