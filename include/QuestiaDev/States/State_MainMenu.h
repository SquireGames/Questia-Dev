#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/Utl/Controls/Input.h"

class State_MainMenu : public State
{
public:
	//TODO make getting eng in a state automated
	State_MainMenu();
	void init();
	~State_MainMenu();
	
	

	//TODO remove and fix state virtual function
	void processImput(sf::Keyboard::Key key, bool isPressed) {}
	
	void processImput(ctr::Input key, bool isPressed);
	void update(sf::Time elapsedTime);
	void displayTextures();
};

#endif // STATE_MAINMENU_H