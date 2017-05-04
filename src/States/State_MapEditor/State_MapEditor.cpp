#include "QuestiaDev/States/State_MapEditor/State_MapEditor.h"

State_MapEditor::State_MapEditor()
{

}

void State_MapEditor::init()
{
	//TODO delete tileMap upon destructor
	eng->tile().loadMap("Demo_1", TileMap::TextureMode::All, TileMap::TileMode::Sprite);
	eng->tile().setPosition(100,100);

	eng->guiLd().loadGui(eng->gui(), "tileMapEditor");
}

State_MapEditor::~State_MapEditor()
{
	eng->gui().purgeButtons();
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
