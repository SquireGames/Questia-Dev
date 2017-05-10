#ifndef STATE_MAPEDITOR_H
#define STATE_MAPEDITOR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "QuestiaEng/Engine.h"
#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/GuiManager/TabBar.h"
//TODO remove, just tesing
#include "QuestiaEng/GuiManager/MenuStack.h"

class State_MapEditor : public State
{
public:
	State_MapEditor();
	void init();
	~State_MapEditor();
	
	void processInput(std::u32string const& inputText);
	void update(sf::Time elapsedTime);
	void displayTextures();
	
private:
	sf::View tileMapView;
	sf::View overlayView;
	
	TabBar upperTab;
	int barID_file, barID_edit, barID_view;
	
	//TODO remove, testing
	MenuStack stackA;
	int stackID_A, stackID_B, stackID_C;
	
};

#endif // STATE_MAPEDITOR_H
