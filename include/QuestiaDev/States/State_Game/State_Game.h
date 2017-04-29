#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/Engine.h"

class State_Game : public State
{
public:
	State_Game();
	void init();
	~State_Game();
	
	//TODO remove and fix state virtual function
	void processInput(sf::Keyboard::Key key, bool isPressed) {}
	
	void processInput(ctr::Input key, bool isPressed);
	void update(sf::Time elapsedTime);
	void displayTextures();

};

#endif // STATE_GAME_H
