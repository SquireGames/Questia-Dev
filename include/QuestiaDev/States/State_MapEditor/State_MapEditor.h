#ifndef STATE_MAPEDITOR_H
#define STATE_MAPEDITOR_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/Engine.h"

class State_MapEditor : public State
{
public:
	State_MapEditor();
	void init();
	~State_MapEditor();
	
	void processInput(std::u32string const& inputText);
	void update(sf::Time elapsedTime);
	void displayTextures();
};

#endif // STATE_MAPEDITOR_H
