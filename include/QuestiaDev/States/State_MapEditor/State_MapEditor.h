#ifndef STATE_MAPEDITOR_H
#define STATE_MAPEDITOR_H

#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "QuestiaEng/Engine.h"
#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/GuiManager/TabBar.h"
#include "QuestiaEng/GuiManager/QueryWindow.h"

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
	enum class Mode {TileMap, TileChoice} mode = Mode::TileMap;
	enum class Selection {none, tile, span} selection = Selection::tile;

	utl::Vector2i mapPos;
	utl::Vector2i sheetPos;

	sf::View overlayView;
	sf::View tileMapView;
	sf::View tileSheetView;

	TabBar mainTab;
	TabBar mapEditTab;
	
	QueryWindow qNewMap;
	QueryWindow qOpenMap;
	QueryWindow qSaveMapAs;
	
	utl::Toggler tg_fullScreen;
	utl::EdgeDetector key_fullScreen;
	
	utl::Toggler tg_grid;
	
	utl::Vector2i selectedTile;
	int tileID = -7;
	
	int moveSpeed = 5;
	float mapZoomRatio = 1;
	float sheetZoomRatio = 1;
	
};

#endif // STATE_MAPEDITOR_H
