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

	virtual void init() = 0;
	virtual void processInput(std::u32string const& inputText) = 0;
	virtual void update(sf::Time elapsedTime) = 0;
	virtual void displayTextures() = 0;

protected:
	Engine* eng = nullptr;
	
private:
	friend class StateManager;
};

#endif // STATE_H
