#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/Utl/Controls/Input.h"

class State_Game : public State
{
public:
	State_Game();
	void init();
	~State_Game();
	
	//TODO remove and fix state virtual function
	void processImput(sf::Keyboard::Key key, bool isPressed) {}
	
	void processImput(ctr::Input key, bool isPressed);
	void update(sf::Time elapsedTime);
	void displayTextures();

};

#endif // STATE_GAME_H
