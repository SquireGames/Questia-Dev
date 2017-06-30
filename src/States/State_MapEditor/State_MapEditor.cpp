#include "QuestiaDev/States/State_MapEditor/State_MapEditor.h"

State_MapEditor::State_MapEditor():
	mapPos(0,0)
	, sheetPos(0,0)
	, overlayView(sf::FloatRect(0,0,1920,1080))
	, tileMapView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, tileSheetView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, mainTab(utl::Direction::up)
	, mapEditTab(utl::Direction::up, 22)
	, mapStatus(utl::Direction::down)
	, tg_fullScreen(true)
	, key_fullScreen(false)
	, tg_grid(true)
	, tg_border(true)
	, selectedTile(-1, -1)
	, selectedSpan(-1, -1)
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

	mainTab.addTab("View");
	mainTab.addEntry("Toggle Grid", "toggleGrid");
	mainTab.addEntry("Bordering Maps", "toggleBorder");
	mainTab.addSpace(50);
	mainTab.addTab("Map", "viewMap");
	mainTab.addTab("Tile Sheet", "viewSheet");
	mainTab.init("mTab", eng->gui(), eng->guiLd());
	eng->guiH().reg(&mainTab);

	mapEditTab.addTab("Tool");
	mapEditTab.addEntry("None", "sel_none");
	mapEditTab.addEntry("Single Tile", "sel_tile");
	mapEditTab.addEntry("Span", "sel_span");
	mapEditTab.addEntry("Erasor", "sel_eras");
	mapEditTab.addTab("Border");
	mapEditTab.addEntry("Change Border", "bor_add");
	mapEditTab.addEntry("Border Offset", "bor_off");
	mapEditTab.init("eTab", eng->gui(), eng->guiLd());
	mapEditTab.setBelow(mainTab);
	eng->guiH().reg(&mapEditTab);

	mapStatus.track("x: ", 0, 45);
	mapStatus.track("y: ", 0, 45);
	mapStatus.track("layer: ", "none", 20);
	mapStatus.addSpace(50);
	mapStatus.track("selected tile: ", "none", 200);
	mapStatus.addSpace(120);
	mapStatus.track("width: ", 0, 45);
	mapStatus.track("height: ", 0, 45);
	mapStatus.track("layers: ", 0, 45);
	mapStatus.addSpace(50);
	int mapNameSpace = 100;
	mapStatus.track("map: ", "none", mapNameSpace);
	mapStatus.track("up: ", "none", mapNameSpace);
	mapStatus.track("right: ", "none", mapNameSpace);
	mapStatus.track("down: ", "none", mapNameSpace);
	mapStatus.track("left: ", "none", mapNameSpace);
	mapStatus.init("mStats", eng->gui(), eng->guiLd());
	eng->guiH().reg(&mapStatus);

	///Queries
	//New map
	qNewMap.addQuery("map_name", "Map Name: ", QueryWindow::QueryType::Input_string);
	qNewMap.addQuery("map_x", "Width: ",  QueryWindow::QueryType::Input_int);
	qNewMap.addQuery("map_y", "Height: ", QueryWindow::QueryType::Input_int);
	qNewMap.addQuery("map_z", "Layers: ", QueryWindow::QueryType::Input_int);
	qNewMap.init("New Map", eng->gui(), &eng->guiLd(), [&]()
	{
		std::string mapName;
		int x, y, z;

		//get window data
		mapName = qNewMap.getResult_string("map_name");
		x = std::max(1, qNewMap.getResult_int("map_x"));
		y = std::max(1, qNewMap.getResult_int("map_y"));
		z = std::min(9, std::max(1, qNewMap.getResult_int("map_z")));

		eng->tileEd().createMap(mapName, x, y, z);
		eng->tileEd().closeMap();
		eng->tileEd().loadMap(mapName);

		mapStatus.updateVal("width: ", x);
		mapStatus.updateVal("height: ", y);
		mapStatus.updateVal("layers: ", z);
		mapStatus.updateVal("map: ", mapName);
		mapStatus.updateVal("up: ", eng->tileEd().getBorderMap(utl::Direction::up));
		mapStatus.updateVal("right: ", eng->tileEd().getBorderMap(utl::Direction::right));
		mapStatus.updateVal("down: ", eng->tileEd().getBorderMap(utl::Direction::down));
		mapStatus.updateVal("left: ", eng->tileEd().getBorderMap(utl::Direction::left));

		qOpenMap.addQuery("choice", mapName, QueryWindow::QueryType::Choice_string);
		qOpenMap.reInit();
		qBorderMapSelec.addQuery("choice", mapName, QueryWindow::QueryType::Choice_string);
		qBorderMapSelec.reInit();

		qNewMap.resetQueries();

		tileID = -7;
		mapStatus.updateVal("selected tile: ", "none");
	});
	eng->guiH().reg(&qNewMap);
	eng->guiH().regInput(&qNewMap);
	//Open Map
	for(auto& it : utl::getFiles("Data/Maps", false))
	{
		qOpenMap.addQuery("choice", it, QueryWindow::QueryType::Choice_string);
	}
	qOpenMap.init("Open Map", eng->gui(), &eng->guiLd(), [&]()
	{
		eng->tileEd().overrideMap();
		eng->tileEd().closeMap();
		eng->tileEd().loadMap(qOpenMap.getChoice_string());

		mapStatus.updateVal("width: ", eng->tileEd().getMapWidth());
		mapStatus.updateVal("height: ", eng->tileEd().getMapHeight());
		mapStatus.updateVal("layers: ", eng->tileEd().getMapLayers());
		mapStatus.updateVal("map: ", qOpenMap.getChoice_string());
		mapStatus.updateVal("up: ", eng->tileEd().getBorderMap(utl::Direction::up));
		mapStatus.updateVal("right: ", eng->tileEd().getBorderMap(utl::Direction::right));
		mapStatus.updateVal("down: ", eng->tileEd().getBorderMap(utl::Direction::down));
		mapStatus.updateVal("left: ", eng->tileEd().getBorderMap(utl::Direction::left));
		tileID = -7;
		mapStatus.updateVal("selected tile: ", "none");
	});
	eng->guiH().reg(&qOpenMap);
	eng->guiH().regInput(&qOpenMap);
	//Save map as
	qSaveMapAs.addQuery("map_name", "Map Name: ",QueryWindow::QueryType::Input_string);
	qSaveMapAs.init("Save As",  eng->gui(), &eng->guiLd(), [&]()
	{
		eng->tileEd().overrideMap();
		eng->tileEd().changeMapName(qSaveMapAs.getResult_string("map_name"));
		eng->tileEd().createMap(qSaveMapAs.getResult_string("map_name"), eng->tileEd().getMapWidth(), eng->tileEd().getMapHeight(), eng->tileEd().getMapLayers());
		eng->tileEd().overrideMap();
		qOpenMap.addQuery("choice", qSaveMapAs.getResult_string("map_name"), QueryWindow::QueryType::Choice_string);
		qOpenMap.reInit();
		qBorderMapSelec.addQuery("choice", qSaveMapAs.getResult_string("map_name"), QueryWindow::QueryType::Choice_string);
		qBorderMapSelec.reInit();
		mapStatus.updateVal("map: ", qSaveMapAs.getResult_string("map_name"));
		qSaveMapAs.resetQueries();
	});
	eng->guiH().reg(&qSaveMapAs);
	eng->guiH().regInput(&qSaveMapAs);

	//Bordering maps
	//qBorderMapDir is used for both chosing a border map (qBorderMapSelec) and chosing a border map offset(qBorderMapOff)
	//the direction and which qBorder window are 'saved' using qBorderDirection and qBorderMode respectively


	//direction selection
	qBorderMapDir.addQuery("choice", "Up", QueryWindow::QueryType::Choice_string);
	qBorderMapDir.addQuery("choice", "Right", QueryWindow::QueryType::Choice_string);
	qBorderMapDir.addQuery("choice", "Down", QueryWindow::QueryType::Choice_string);
	qBorderMapDir.addQuery("choice", "Left", QueryWindow::QueryType::Choice_string);
	qBorderMapDir.init("Border Direction", eng->gui(), &eng->guiLd(), [&]()
	{
		const std::string& choice = qBorderMapDir.getChoice_string();
		qBorderDirection = (choice == "Up") ? utl::Direction::up :
		                   (choice == "Right") ? utl::Direction::right :
		                   (choice == "Down") ? utl::Direction::down :
		                   utl::Direction::left;
		switch(qBorderMode)
		{
		case qDirMode::BorderName:
			qBorderMapSelec.setActive(true);
			break;
		case qDirMode::BorderOffset:
			qBorderMapOffset.setActive(true);
			break;
		}
		qBorderMapDir.resetQueries();
	});
	eng->guiH().reg(&qBorderMapDir);
	eng->guiH().regInput(&qBorderMapDir);

	//border map offset selection
	qBorderMapOffset.addQuery("offset", "Offset: ", QueryWindow::QueryType::Input_int);
	qBorderMapOffset.init("Border Offset", eng->gui(), &eng->guiLd(), [&]()
	{
		eng->tileEd().changeBorderOffset(qBorderDirection, qBorderMapOffset.getResult_int("offset"));
		qBorderMapOffset.resetQueries();
	});
	eng->guiH().reg(&qBorderMapOffset);
	eng->guiH().regInput(&qBorderMapOffset);

	//border map selection
	for(auto& it : utl::getFiles("Data/Maps", false))
	{
		qBorderMapSelec.addQuery("choice", it, QueryWindow::QueryType::Choice_string);
	}
	qBorderMapSelec.addQuery("choice", "None", QueryWindow::QueryType::Choice_string);
	qBorderMapSelec.init("Border Selection", eng->gui(), &eng->guiLd(), [&]()
	{
		if(qBorderMapSelec.getChoice_string() == "None")
		{
			eng->tileEd().changeBorderMap(qBorderDirection, std::string());
		}
		else
		{
			eng->tileEd().changeBorderMap(qBorderDirection, qBorderMapSelec.getChoice_string());
		}
		mapStatus.updateVal("up: ", eng->tileEd().getBorderMap(utl::Direction::up));
		mapStatus.updateVal("right: ", eng->tileEd().getBorderMap(utl::Direction::right));
		mapStatus.updateVal("down: ", eng->tileEd().getBorderMap(utl::Direction::down));
		mapStatus.updateVal("left: ", eng->tileEd().getBorderMap(utl::Direction::left));
		qBorderMapSelec.resetQueries();
	});

	eng->guiH().reg(&qBorderMapSelec);
	eng->guiH().regInput(&qBorderMapSelec);

}

State_MapEditor::~State_MapEditor()
{
	eng->tileEd().overrideMap();
	eng->guiH().clear();
	eng->gui().purgeButtons();
	eng->tileEd().closeMap();
}

void State_MapEditor::processInput(std::u32string const& inputText)
{

}

void State_MapEditor::update(sf::Time elapsedTime)
{
	//tab to toggle fullscreen map view
	if(key_fullScreen.risingEdge(ctr::checkInput(ctr::Input::Tab)) && !isGuiHovered())
	{
		mainTab.setActivity(tg_fullScreen.toggle());
		mapEditTab.setActivity(tg_fullScreen.getState() && mode == Mode::TileMap);
		mapStatus.setActivity(tg_fullScreen.getState());
	}
	//select layer
	for(int keyIt = 0; (keyIt < 8) && (keyIt < (int)eng->tileEd().getMapLayers()) && !isGuiHovered(); keyIt++)
	{
		ctr::Input key = static_cast<ctr::Input>((int)ctr::Input::Num1 + keyIt);
		if(ctr::checkInput(key))
		{
			selectedLayer = keyIt;
			mapStatus.updateVal("layer: ", selectedLayer + 1);
			break;
		}
	}
	if(ctr::checkInput(ctr::Input::Tilde) && !isGuiHovered())
	{
		selectedLayer = -1;
		mapStatus.updateVal("layer: ", "none");
		eng->tileEd().resetTileAlpha();
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
		break;
	case -1:
		currentView.zoom(1.20);
		break;
	default:
		break;
	}
	eng->tileEd().setViewportSize(currentView.getSize().x, currentView.getSize().y);
	zoomRatio = (currentView.getSize().x / 1920.f);

	//move around map with wasd keys
	int moveDistance = moveSpeed * std::max(0.5f, zoomRatio) * !isQueryHovered();
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

	mapStatus.updateVal("x: ", selectedTile.x);
	mapStatus.updateVal("y: ", selectedTile.y);

	//handle gui
	if(eng->mouse().isMousePressed(ctr::Input::LMouse))
	{
		//handle gui input
		if(eng->gui().isClicked("newMap"))
		{
			if(!isQueryHovered())
			{
				qNewMap.setActive(true);
			}
		}
		else if(eng->gui().isClicked("openMap"))
		{
			if(!isQueryHovered())
			{
				qOpenMap.setActive(true);
			}
		}
		else if(eng->gui().isClicked("save"))
		{
			eng->tileEd().overrideMap();
		}
		else if(eng->gui().isClicked("saveAs"))
		{
			if(!isQueryHovered())
			{
				qSaveMapAs.setActive(true);
			}
		}
		else if(eng->gui().isClicked("toggleGrid"))
		{
			eng->tileEd().showGridLines(tg_grid.toggle());
		}
		else if(eng->gui().isClicked("toggleBorder"))
		{
			eng->tileEd().showBorderMaps(tg_border.toggle());
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
			eng->tileEd().resetTileAlpha();
		}
		else if(eng->gui().isClicked("sel_none"))
		{
			selection = Selection::none;
		}
		else if(eng->gui().isClicked("sel_tile"))
		{
			selection = Selection::tile;
		}
		else if(eng->gui().isClicked("sel_span"))
		{
			selection = Selection::span;
		}
		else if(eng->gui().isClicked("sel_eras"))
		{
			tileID = 0;
			mapStatus.updateVal("selected tile: ", "Erasor");
		}
		else if(eng->gui().isClicked("bor_add"))
		{
			if(!isQueryHovered())
			{
				qBorderMode = qDirMode::BorderName;
				qBorderMapDir.setActive(true);
			}
		}
		else if(eng->gui().isClicked("bor_off"))
		{
			if(!isQueryHovered())
			{
				qBorderMode = qDirMode::BorderOffset;
				qBorderMapDir.setActive(true);
			}
		}
	}
	if(!isGuiHovered())
	{
		//handle tile selection
		switch(mode)
		{
		case Mode::TileMap:
			{
				switch(selection)
				{
				case Selection::none:
					break;
				case Selection::tile:
					{
						if(eng->mouse().isMouseHeld(ctr::Input::LMouse) && (selectedLayer >= 0))
						{
							eng->tileEd().replaceTile(tileID, selectedTile.x, selectedTile.y, selectedLayer);
						}
					}
					break;
				case Selection::span:
					{
						if(eng->mouse().isMousePressed(ctr::Input::LMouse))
						{
							selectedSpan = selectedTile;
							wasHeld = true;
						}
						if(eng->mouse().isMouseReleased(ctr::Input::LMouse) && wasHeld && (selectedLayer >= 0))
						{
							for(int i_x = selectedSpan.x; i_x != selectedTile.x + ((selectedSpan.x < selectedTile.x) ? 1 : -1); i_x += (selectedSpan.x < selectedTile.x) ? 1 : -1)
							{
								for(int i_y = selectedSpan.y; i_y != selectedTile.y + ((selectedSpan.y < selectedTile.y) ? 1 : -1); i_y += (selectedSpan.y < selectedTile.y) ? 1 : -1)
								{
									eng->tileEd().replaceTile(tileID, i_x, i_y, selectedLayer);
								}
							}
							wasHeld = false;
						}
						if(!eng->mouse().isMouseHeld(ctr::Input::LMouse))
						{
							wasHeld = false;
						}
					}
					break;
				}
			}
			break;
		case Mode::TileChoice:
			{
				if(eng->mouse().isMousePressed(ctr::Input::LMouse))
				{
					if(eng->tileEd().getTile_tileState(selectedTile.x, selectedTile.y) != nullptr)
					{
						tileID = eng->tileEd().getTileID(eng->tileEd().getTile_tileState(selectedTile.x, selectedTile.y)->getDisplay());
						mapStatus.updateVal("selected tile: ", eng->tileEd().getTile_tileState(selectedTile.x, selectedTile.y)->getDisplay());
					}
				}
			}
			break;
		}
	}
}

void State_MapEditor::displayTextures()
{
	switch(mode)
	{
	case Mode::TileMap:
		eng->win().setView(tileMapView);
		{
			if(selectedLayer < 0)
			{
				eng->tileEd().draw();
			}
			else
			{
				for(int layer = 0; layer < (int) eng->tileEd().getMapLayers(); layer++)
				{
					if(layer < selectedLayer)
					{
						eng->tileEd().drawLayer(layer, 50);
					}
					else if(layer == selectedLayer)
					{
						eng->tileEd().drawLayer(layer, 100);
					}
					else if(layer == selectedLayer + 1)
					{
						eng->tileEd().drawLayer(layer, 25);
					}
					else if(layer == selectedLayer + 2)
					{
						eng->tileEd().drawLayer(layer, 7);
					}
				}
			}
		}
		eng->tileEd().drawGridLines();
		{
			if(!eng->tileEd().isLoaded() || isGuiHovered()) {break;}
			switch(selection)
			{
			case Selection::none:
				break;
			case Selection::tile:
				eng->tileEd().hoverTile(selectedTile.x, selectedTile.y);
				break;
			case Selection::span:
				{
					if(eng->mouse().isMouseHeld(ctr::Input::LMouse))
					{
						eng->tileEd().hoverSpan(selectedTile.x, selectedTile.y,
						                        selectedSpan.x - selectedTile.x + (selectedSpan.x - selectedTile.x >= 0) - (selectedSpan.x - selectedTile.x < 0),
						                        selectedSpan.y - selectedTile.y + (selectedSpan.y - selectedTile.y >= 0) - (selectedSpan.y - selectedTile.y < 0));
					}
				}
				break;
			}
		}
		break;
	case Mode::TileChoice:
		eng->win().setView(tileSheetView);
		eng->tileEd().drawTiles(*eng->gui().getFont());
		if(eng->tileEd().isLoaded() && !isGuiHovered()) {eng->tileEd().hoverTile(selectedTile.x, selectedTile.y);}
		break;
	}

	//draw the gui
	eng->win().setView(overlayView);
	eng->gui().draw();
}

bool State_MapEditor::isGuiHovered()
{
	return mainTab.isHovered() || mapEditTab.isHovered() || isQueryHovered();
}

bool State_MapEditor::isQueryHovered()
{
	return qNewMap.isActive() || qOpenMap.isActive() || qSaveMapAs.isActive() || qBorderMapDir.isActive() || qBorderMapSelec.isActive() || qBorderMapOffset.isActive();
}
