#include "QuestiaDev/Application.h"

Application::Application():
	eng("Questia Editor", 128, 0, 0, 0, "Alpha")
{
	eng.guiLd().setGuiPack("Default");
	
	//enforce windowed mode
	if(eng.sv().getWindowMode() != 1)
	{
		eng.win().create(sf::VideoMode(1920, 1080), "Questia Editor", sf::Style::Default, sf::ContextSettings(0,0,16));
		eng.sv().saveOption(eng.sv().getWindowMode_name(), "1");
		eng.sv().writeOptions();
	}
	
	eng.win().setVerticalSyncEnabled(true);
	
	eng.state().reg("MainMenu", 	[]() {return new State_MainMenu();});
	eng.state().reg("OptionsMenu",  []() {return new State_OptionsMenu();});
	eng.state().reg("MapEditor",    []() {return new State_MapEditor();});
	eng.state().reg("Loading",  	[]() {return new State_Loading();});
	
	eng.state().changeState("MainMenu");
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
