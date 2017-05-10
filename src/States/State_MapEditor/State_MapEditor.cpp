#include "QuestiaDev/States/State_MapEditor/State_MapEditor.h"

State_MapEditor::State_MapEditor():
	tileMapView(sf::FloatRect(0,0,1920,1080))
	, overlayView(sf::FloatRect(1920/2,1080/2,1920,1080))
	, upperTab(utl::Direction::up)
	, stackA(utl::Direction::up)
{

}

void State_MapEditor::init()
{
	//eng->guiLd().loadGui(eng->gui(), "tileMapEditor");
	
	//eng->tile().loadMap("Demo_1", TileMap::TextureMode::All, TileMap::TileMode::Sprite);
	//eng->tile().setPosition(100,100);

	barID_file = upperTab.addTab("File");
	barID_edit = upperTab.addTab("Edit");
	barID_view = upperTab.addTab("View");
	upperTab.init("uTab", eng->gui(), eng->guiLd());
	eng->guiH().reg(&upperTab);
	
	stackID_A = stackA.addEntry("A");
	stackID_B = stackA.addEntry("B");
	stackID_B = stackA.addEntry("C");
	stackA.init("stackTEST", 0, 90, eng->gui(), eng->guiLd());
	eng->guiH().reg(&stackA);
}

State_MapEditor::~State_MapEditor()
{
	eng->guiH().clear();
	eng->gui().purgeButtons();
	eng->tile().closeMap();
}

void State_MapEditor::processInput(std::u32string const& inputText)
{

}

void State_MapEditor::update(sf::Time elapsedTime)
{
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		
	}
}
void State_MapEditor::displayTextures()
{
	eng->tile().draw();
	eng->gui().drawButtons();
}
