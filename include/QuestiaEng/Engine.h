#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics/RenderWindow.hpp>

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/Data/InputBuffer.h"
#include "QuestiaEng/GuiManager/GuiManager.h"

class Engine
{
public:
	//ctor + dtor
	Engine(std::string windowName, int tickRate);
	~Engine() = default;

	//runtime loop function
	bool run();
	bool tick();
	void processInput();
	void render();
	
	//used in a state
	void terminate() {toTerminate = true;}

	//interfaces
	ResourceManager& 	res() {return resourceManager;}
	InputBuffer& 		inp() {return inputBuffer;}
	GuiManager&			gui() {return guiManager;}

private:
	sf::RenderWindow window;

	ResourceManager resourceManager;
	InputBuffer inputBuffer;
	GuiManager guiManager;

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time timeSinceLastTick;
	
	bool toTerminate = false;
};

#endif // ENGINE_H
