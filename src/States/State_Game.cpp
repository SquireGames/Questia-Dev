#include "QuestiaDev/States/State_Game.h"

#include "QuestiaEng/Engine.h"

State_Game::State_Game()
{

}

void State_Game::init()
{
	//TODO delete tileMap upon destructor
	eng->tile().loadMap("Demo_1", TileEng::TextureMode::Map, TileEng::TileMode::Batch);
	eng->tile().setPosition(100,100);
	
	
	eng->guiLd().loadGui(eng->gui(), "game");
	
	for(int i = 0; i < 50000000; i++)
	{
		for(int j = 0; j < 50000000; j++)
		{	
			j += i;
		}
	}
}

State_Game::~State_Game()
{
	eng->gui().purgeButtons();
}

void State_Game::processImput(ctr::Input key, bool isPressed)
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
