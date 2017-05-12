#include "QuestiaDev/States/State_MapEditor/State_MapEditor.h"

State_MapEditor::State_MapEditor():
	pos(0,0)
	, overlayView(sf::FloatRect(0,0,1920,1080))
	, tileMapView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, upperTab(utl::Direction::up)
	, tg_fullScreen(true)
	, key_fullScreen(false)
	, tg_grid(true)
	, selectedTile(-1, -1)
{

}

void State_MapEditor::init()
{
	//gui
	upperTab.addTab("File");
	upperTab.addEntry("New Map", "newMap");
	upperTab.addEntry("Open Map", "openMap");
	upperTab.addEntry("Save", "save");
	upperTab.addEntry("Save as", "saveAs");

	upperTab.addTab("Edit");
	upperTab.addEntry("Undo", "undo");
	upperTab.addEntry("Redo", "redo");

	upperTab.addTab("View");
	upperTab.addEntry("Toggle Grid", "toggleGrid");

	upperTab.init("uTab", eng->gui(), eng->guiLd());
	eng->guiH().reg(&upperTab);
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
		upperTab.setActivity(tg_fullScreen.toggle());
		eng->tileEd().closeMap();
	}

	//zoom
	const int zoom = eng->mouse().getScroll();
	switch(zoom)
	{
	case 1:
		tileMapView.zoom(0.80);
		eng->tileEd().setViewportSize(tileMapView.getSize().x, tileMapView.getSize().y);
		break;
	case -1:
		tileMapView.zoom(1.20);
		eng->tileEd().setViewportSize(tileMapView.getSize().x, tileMapView.getSize().y);
		break;
	default:
		break;
	}
	mapZoomRatio = (tileMapView.getSize().x / 1920.f);

	//move around map with wasd keys
	int moveDistance = moveSpeed * std::max(0.5f, mapZoomRatio);
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
	tileMapView.setCenter(pos.x, pos.y);

	//handle mouse hover
	utl::Vector2f mousePos = eng->mouse().getMousePos();
	mousePos = (mousePos * mapZoomRatio) - (utl::Vector2f(1920/2, 1080/2) * mapZoomRatio) + utl::Vector2f(tileMapView.getCenter());
	mousePos = mousePos / 64.f;
	mousePos.x = std::floor(mousePos.x);
	mousePos.y = std::floor(mousePos.y);
	selectedTile = utl::Vector2i((int)mousePos.x, (int)mousePos.y);

	//handle gui
	if(eng->mouse().isMousePressed(ctr::Input::LMouse))
	{
		if(eng->gui().isClicked("openMap"))
		{
			eng->tileEd().closeMap();
			eng->tileEd().loadMap("Demo_1");
		}
		else if(eng->gui().isClicked("toggleGrid"))
		{
			eng->tileEd().showGridLines(tg_grid.toggle());
		}
	}
}
void State_MapEditor::displayTextures()
{
	//draw the map
	eng->win().setView(tileMapView);
	eng->tileEd().draw();
	eng->tileEd().drawGridLines();
	if(eng->tileEd().isLoaded()) {eng->tileEd().hoverTile(selectedTile.x, selectedTile.y);}

	//draw the gui
	eng->win().setView(overlayView);
	eng->gui().drawButtons();
}
