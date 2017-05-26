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

void State_MainMenu::processInput(std::u32string const& inputText)
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
		else if(eng->gui().isClicked("editMap"))
        {
			eng->state().transitionState("MapEditor", "Loading");
        }
	}
}

void State_MainMenu::displayTextures()
{
	eng->gui().draw();
}

