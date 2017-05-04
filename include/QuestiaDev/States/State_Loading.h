#ifndef STATE_LOADING_H
#define STATE_LOADING_H

#include "SFML/Graphics.hpp"

#include "QuestiaEng/Engine.h"

#include "QuestiaEng/StateManager/State.h"

class State_Loading : public State
{
public:
	State_Loading();
	~State_Loading();

	virtual void displayTextures();
	virtual void init();
	virtual void processInput(std::u32string const& inputText);
	virtual void update(sf::Time elapsedTime);

private:
	sf::Sprite loadSprite;
	sf::Sprite backSprite;
};

#endif // STATE_LOADING_H
