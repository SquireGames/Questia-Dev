#include "QuestiaDev/States/State_MainMenu/State_MainMenu.h"

State_MainMenu::State_MainMenu()
{
	
}

void State_MainMenu::init()
{
	eng->guiLd().loadGui(eng->gui(), "mainMenu");
}

State_MainMenu::~State_MainMenu()
{
	eng->gui().purgeButtons();
}

void State_MainMenu::processInput(ctr::Input key, bool isPressed)
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
		else if(eng->gui().isClicked("play"))
        {
			//TODO change state outside of state itself
			eng->state().transitionState("Game", "Loading");
        }
	}
}

void State_MainMenu::displayTextures()
{
	eng->gui().drawButtons();
}

