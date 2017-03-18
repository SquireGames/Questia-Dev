#include "QuestiaDev/States/State_MainMenu.h"

#include "QuestiaEng/Engine.h"

State_MainMenu::State_MainMenu()
{
	
}

void State_MainMenu::init()
{
	eng->tile().loadMap("Demo_1", TileEng::TextureMode::Map, TileEng::TileMode::Batch);
	eng->tile().setPosition(100,100);
	
	eng->guiLd().setGuiPack("Default");
	//eng->guiLd().loadGui(eng->gui(), "mainMenu");
}

State_MainMenu::~State_MainMenu()
{
	
}

void State_MainMenu::processImput(ctr::Input key, bool isPressed)
{
	
}

void State_MainMenu::update(sf::Time elapsedTime)
{
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		if(eng->gui().isClicked("exit"))
		{
			eng->terminate();
		}
	}
}

void State_MainMenu::displayTextures()
{
	eng->tile().drawMap();
	eng->gui().drawButtons();
}

