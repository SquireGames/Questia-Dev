#ifndef STATE_OPTIONSMENU_H
#define STATE_OPTIONSMENU_H

#include "QuestiaEng/StateManager/State.h"

class State_OptionsMenu : public State
{
public:
	State_OptionsMenu();
	~State_OptionsMenu();

	virtual void displayTextures();
	virtual void init();
	virtual void processInput(std::u32string const& inputText);
	virtual void update(sf::Time elapsedTime);
};

#endif // STATE_OPTIONSMENU_H
