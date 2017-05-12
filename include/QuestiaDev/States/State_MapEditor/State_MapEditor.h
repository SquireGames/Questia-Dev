#ifndef STATE_MAPEDITOR_H
#define STATE_MAPEDITOR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "QuestiaEng/Engine.h"
#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/GuiManager/TabBar.h"

#include "QuestiaEng/Utl/Toggler.h"
#include "QuestiaEng/Utl/EdgeDetector.h"

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
	utl::Vector2i pos;

	sf::View overlayView;
	sf::View tileMapView;

	TabBar upperTab;
	
	utl::Toggler tg_fullScreen;
	utl::EdgeDetector key_fullScreen;
	
	utl::Toggler tg_grid;
	
	utl::Vector2i selectedTile;
	
	float mapZoomRatio = 1;
	int moveSpeed = 5;
	
};

#endif // STATE_MAPEDITOR_H
