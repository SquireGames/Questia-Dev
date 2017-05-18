#ifndef TABBAR_H
#define TABBAR_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"
#include "QuestiaEng/GuiManager/GuiElement/MenuStack.h"

class TabBar : public GuiElement
{
public:
	TabBar(utl::Direction direction, int offset = 0);
	~TabBar();

	int addTab(std::string text, std::string buttonName = std::string());
	void addSpace(int tabID, int spacing);
	void addSpace(int spacing);
	void addEntry(int tabID, std::string entryText, std::string buttonName);
	void addEntry(std::string entryText, std::string buttonName);
	void init(std::string tabBarName, GuiManager& pGuiManager, GuiLoader& guiLoader);

	//if one tab bar is right below another, to prevent double selection
	void setBelow(TabBar& other);

	//automatically called if MenuStack is registered into GuiHandler
	void update(MouseListener& mouse);

	void setActivity(bool isActive);
	bool isActive() {return isTabBarActive;}
	bool isHovered() {return isTabBarHovered && isTabBarActive;}

private:
	GuiManager* guiManager;

	bool isTabBarActive = true;
	bool isTabBarHovered = false;
	bool isHoverable = true;
	int mostRecentTab = 0;

	struct Tab
	{
		Tab(std::string pTabName, std::string bName, utl::Direction dir):tabName(pTabName), buttonName(bName), menu((dir == utl::Direction::down) ? utl::Direction::up : utl::Direction::down) {}
		std::string tabName;
		std::string buttonName;
		MenuStack menu;
		int offset = 0;
	};

	void allowHover(bool canHover)
	{
		if(canHover != isHoverable)
		{
			isHoverable = canHover;
			for(Tab& tab : tabs)
			{
				guiManager->setButton(tab.buttonName, gui::ButtonCharacteristic::isActive, isHoverable);
			}
		}
	}

	std::vector<Tab> tabs;

	std::string groupName;
	std::string button_bar;

	TabBar* otherBar = nullptr;

	utl::Direction dir = utl::Direction::up;
	int offset_y = 0;
};

#endif // TABBAR_H
