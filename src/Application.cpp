#include "QuestiaDev/Application.h"

Application::Application():
	eng("Questia", 128)
{
	std::cout << "--------------------" << std::endl;
	std::cout << "  Questia Executed  " << std::endl;
	std::cout << "--------------------" << std::endl;
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
		}
		
		//render when possible, but only to the framerate limit
		eng.render();
	}
}


