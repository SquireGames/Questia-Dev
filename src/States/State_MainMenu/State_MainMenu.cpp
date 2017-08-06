#include "QuestiaDev/States/State_MainMenu/State_MainMenu.h"

State_MainMenu::State_MainMenu()
{
	
}

void State_MainMenu::init()
{
	GuiBuilder& guiBuilder = eng->gui().edit();
	
	eng->gui().loadGui("mainMenu");
	guiBuilder.setBtnAtr("versionText", "text", gui::BtnAtrChar::text, guiBuilder.getText("T_QDevTools") + U" " + utl::toU32(eng->getVersion()));
	guiBuilder.setBtnAtr("versionText_eng", "text", gui::BtnAtrChar::text, guiBuilder.getText("T_Eng_Version") + U" " + utl::toU32(eng->getVersion_eng()));
}

State_MainMenu::~State_MainMenu()
{
	eng->gui().edit().purgeButtons();
	std::cout << "Closing Main Menu" << std::endl;
}

void State_MainMenu::processInput(std::u32string const& inputText)
{
	
}

void State_MainMenu::update(sf::Time elapsedTime)
{
	if(eng->mouse().isMouseReleased(ctr::Input::LMouse))
	{
		if(eng->gui().isHovered("exit"))
		{
			eng->terminate();
		}
		else if(eng->gui().isHovered("editMap"))
        {
			eng->state().changeState("MapEditor");
        }
	}
}

void State_MainMenu::displayTextures()
{
	eng->gui().draw();
}

