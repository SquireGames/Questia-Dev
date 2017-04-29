#ifndef STATE_H
#define STATE_H

#include <iostream>

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics.hpp"

//forward declarations
class Engine;
class StateManager;

class State
{
public:
	State() = default;
	virtual ~State();

	//TODO make this a pure virtual function once legacy states are out!
	virtual void init();
	virtual void processInput(sf::Keyboard::Key key, bool isPressed) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
	virtual void displayTextures() = 0;

	//TODO fully implement engine automation	
protected:
	Engine* eng = nullptr;
	
private:
	friend class StateManager;
};

#endif // STATE_H
