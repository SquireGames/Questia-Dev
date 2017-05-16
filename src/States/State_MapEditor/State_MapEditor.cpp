#include "QuestiaDev/States/State_MapEditor/State_MapEditor.h"

State_MapEditor::State_MapEditor():
	mapPos(0,0)
	, sheetPos(0,0)
	, overlayView(sf::FloatRect(0,0,1920,1080))
	, tileMapView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, tileSheetView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, mainTab(utl::Direction::up)
	, mapEditTab(utl::Direction::up, 22)
	, tg_fullScreen(true)
	, key_fullScreen(false)
	, tg_grid(true)
	, selectedTile(-1, -1)
{

}

void State_MapEditor::init()
{
	///Tabs
	mainTab.addTab("File");
	mainTab.addEntry("New Map", "newMap");
	mainTab.addEntry("Open Map", "openMap");
	mainTab.addEntry("Save", "save");
	mainTab.addEntry("Save as", "saveAs");
	mainTab.addTab("Edit");
	mainTab.addEntry("Undo", "undo");
	mainTab.addEntry("Redo", "redo");
	mainTab.addTab("View");
	mainTab.addEntry("Toggle Grid", "toggleGrid");
	mainTab.addSpace(50);
	mainTab.addTab("Map", "viewMap");
	mainTab.addTab("Tile Sheet", "viewSheet");
	mainTab.init("mTab", eng->gui(), eng->guiLd());
	eng->guiH().reg(&mainTab);

	mapEditTab.addTab("Tool");
	mapEditTab.addEntry("None", "sel_none");
	mapEditTab.addEntry("Single Tile", "sel_tile");
	mapEditTab.addEntry("Span", "sel_span");
	mapEditTab.init("eTab", eng->gui(), eng->guiLd());
	mapEditTab.setBelow(mainTab);
	eng->guiH().reg(&mapEditTab);

	///Queries
	//New map
	qNewMap.addQuery("map_name", "Map Name: ", QueryWindow::QueryType::Input_string);
	qNewMap.addQuery("map_x", "Width: ",  QueryWindow::QueryType::Input_int);
	qNewMap.addQuery("map_y", "Height: ", QueryWindow::QueryType::Input_int);
	qNewMap.addQuery("map_z", "Layers: ", QueryWindow::QueryType::Input_int);
	qNewMap.init("New Map", eng->gui(), eng->guiLd(), [&]()
	{
		std::string mapName;
		int x, y, z;

		//get window data
		mapName = qNewMap.getResult_string("map_name");
		x = std::max(1, qNewMap.getResult_int("map_x"));
		y = std::max(1, qNewMap.getResult_int("map_y"));
		z = std::max(1, qNewMap.getResult_int("map_z"));

		eng->tileEd().createMap(mapName, x, y, z);
		eng->tileEd().closeMap();
		eng->tileEd().loadMap(mapName);

		qOpenMap.postAddChoice("choice", mapName);
		qNewMap.resetQueries();
	});
	eng->guiH().reg(&qNewMap);
	eng->guiH().regInput(&qNewMap);
	//Open Map
	for(auto& it : utl::getFiles("Maps", false))
	{
		qOpenMap.addQuery("choice", it, QueryWindow::QueryType::Choice_string);
	}
	qOpenMap.init("Open Map", eng->gui(), eng->guiLd(), [&]()
	{
		eng->tileEd().closeMap();
		eng->tileEd().loadMap(qOpenMap.getChoice_string());
	});
	eng->guiH().reg(&qOpenMap);
	eng->guiH().regInput(&qOpenMap);
	//Save map as
	qSaveMapAs.addQuery("map_name", "Map Name: ",QueryWindow::QueryType::Input_string);
	qSaveMapAs.init("Save As",  eng->gui(), eng->guiLd(), [&]()
	{
		eng->tileEd().changeMapName(qSaveMapAs.getResult_string("map_name"));
		eng->tileEd().createMap(qSaveMapAs.getResult_string("map_name"), eng->tileEd().getMapWidth(), eng->tileEd().getMapHeight(), eng->tileEd().getMapLayers());
		eng->tileEd().overrideMap();
		qSaveMapAs.resetQueries();
	});
	eng->guiH().reg(&qSaveMapAs);
	eng->guiH().regInput(&qSaveMapAs);
}

State_MapEditor::~State_MapEditor()
{
	eng->guiH().clear();
	eng->gui().purgeButtons();
	eng->tileEd().closeMap();
}

void State_MapEditor::processInput(std::u32string const& inputText)
{

}

void State_MapEditor::update(sf::Time elapsedTime)
{
	//tilde to toggle fullscreen map view
	if(key_fullScreen.risingEdge(ctr::checkInput(ctr::Input::Tilde)))
	{
		mainTab.setActivity(tg_fullScreen.toggle());
	}

	//differences between mapView and sheetView
	sf::View& currentView = (mode == Mode::TileMap) ? tileMapView : tileSheetView;
	float& zoomRatio = (mode == Mode::TileMap) ? mapZoomRatio : sheetZoomRatio;
	utl::Vector2i& pos = (mode == Mode::TileMap) ? mapPos : sheetPos;

	//zoom
	const int zoom = eng->mouse().getScroll();
	switch(zoom)
	{
	case 1:
		currentView.zoom(0.80);
		eng->tileEd().setViewportSize(currentView.getSize().x, currentView.getSize().y);
		break;
	case -1:
		currentView.zoom(1.20);
		eng->tileEd().setViewportSize(currentView.getSize().x, currentView.getSize().y);
		break;
	default:
		break;
	}
	zoomRatio = (currentView.getSize().x / 1920.f);

	//move around map with wasd keys
	int moveDistance = moveSpeed * std::max(0.5f, zoomRatio);
	if(ctr::checkInput(ctr::Input::W))
	{
		pos.y -= moveDistance;
	}
	if(ctr::checkInput(ctr::Input::S))
	{
		pos.y += moveDistance;
	}
	if(ctr::checkInput(ctr::Input::A))
	{
		pos.x -= moveDistance;
	}
	if(ctr::checkInput(ctr::Input::D))
	{
		pos.x += moveDistance;
	}

	//set view positions
	eng->tileEd().setPosition(pos.x, pos.y);
	currentView.setCenter(pos.x, pos.y);

	//handle mouse hover
	utl::Vector2f mousePos = eng->mouse().getMousePos();
	mousePos = (mousePos * zoomRatio) - (utl::Vector2f(1920/2, 1080/2) * zoomRatio) + utl::Vector2f(currentView.getCenter());
	mousePos = mousePos / 64.f;
	mousePos.x = std::floor(mousePos.x);
	mousePos.y = std::floor(mousePos.y);
	selectedTile = utl::Vector2i((int)mousePos.x, (int)mousePos.y);

	//handle gui
	if(eng->mouse().isMousePressed(ctr::Input::LMouse))
	{
		//handle gui input
		if(eng->gui().isClicked("newMap"))
		{
			qNewMap.setActive(true);
		}
		else if(eng->gui().isClicked("openMap"))
		{
			qOpenMap.setActive(true);
		}
		else if(eng->gui().isClicked("save"))
		{

		}
		else if(eng->gui().isClicked("saveAs"))
		{
			qSaveMapAs.setActive(true);
		}
		else if(eng->gui().isClicked("toggleGrid"))
		{
			eng->tileEd().showGridLines(tg_grid.toggle());
		}
		else if(eng->gui().isClicked("viewMap"))
		{
			mode = Mode::TileMap;
			mapEditTab.setActivity(true);
		}
		else if(eng->gui().isClicked("viewSheet"))
		{
			mode = Mode::TileChoice;
			mapEditTab.setActivity(false);
		}
		//handle tile selection
		else
		{
			switch(mode)
			{
			case Mode::TileMap:
				{
					switch(selection)
					{
					case Selection::none:
						break;
					case Selection::tile:
						break;
					case Selection::span:
						break;
					}
				}
				break;
			case Mode::TileChoice:
				break;
			}
		}
	}
}
void State_MapEditor::displayTextures()
{
	switch(mode)
	{
	case Mode::TileMap:
		eng->win().setView(tileMapView);
		eng->tileEd().draw();
		eng->tileEd().drawGridLines();
		if(eng->tileEd().isLoaded() && !mainTab.isHovered()) {eng->tileEd().hoverTile(selectedTile.x, selectedTile.y);}
		break;
	case Mode::TileChoice:
		eng->win().setView(tileSheetView);
		eng->tileEd().drawTiles(*eng->gui().getFont());
		if(eng->tileEd().isLoaded() && !mainTab.isHovered()) {eng->tileEd().hoverTile(selectedTile.x, selectedTile.y);}
		break;
	}

	//draw the gui
	eng->win().setView(overlayView);
	eng->gui().drawButtons();
}
