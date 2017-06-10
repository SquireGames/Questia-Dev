#include "QuestiaDev/States/State_MainMenu/State_MainMenu.h"

State_MainMenu::State_MainMenu()
{
	
}

void State_MainMenu::init()
{
	eng->guiLd().loadGui(eng->gui(), "mainMenu");
	eng->gui().setBtnAtr("versionText", "text", gui::BtnAtrChar::text, eng->gui().getText("T_QDevTools") + U" " + utl::toU32(eng->getVersion()));
	eng->gui().setBtnAtr("versionText_eng", "text", gui::BtnAtrChar::text, eng->gui().getText("T_Eng_Version") + U" " + utl::toU32(eng->getVersion_eng()));
}

State_MainMenu::~State_MainMenu()
{
	eng->gui().purgeButtons();
	std::cout << "Closing Main Menu" << std::endl;
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
			eng->state().changeState("MapEditor");
        }
	}
}

void State_MainMenu::displayTextures()
{
	eng->gui().draw();
}

