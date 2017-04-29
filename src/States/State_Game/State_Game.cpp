#include "QuestiaDev/States/State_Game/State_Game.h"

State_Game::State_Game()
{

}

void State_Game::init()
{
	//TODO delete tileMap upon destructor
	eng->tile().loadMap("Demo_1", TileMap::TextureMode::Map, TileMap::TileMode::Batch);
	eng->tile().setPosition(100,100);
	
	eng->guiLd().loadGui(eng->gui(), "game");
}

State_Game::~State_Game()
{
	eng->gui().purgeButtons();
}

void State_Game::processInput(ctr::Input key, bool isPressed)
{

}
void State_Game::update(sf::Time elapsedTime)
{
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		
	}
}
void State_Game::displayTextures()
{
	eng->tile().drawMap();
	eng->gui().drawButtons();
}
