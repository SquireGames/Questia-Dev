#ifndef TABBAR_H
#define TABBAR_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

class TabBar : public GuiElement
{
public:
	TabBar(utl::Direction direction);
	~TabBar();

	int addTab(std::string text);
	int addEntry(int tabID, std::string entryName);
	void init(std::string tabBarName, GuiManager& pGuiManager, GuiLoader& guiLoader);
	
	void setActivity(bool isActive) {isTabBarActive = isActive;}
	bool isActive() {return isTabBarActive;}

private:
	GuiManager* guiManager;
	
	bool isTabBarActive = true;

	struct Tab
	{
		Tab(std::string pTabName):tabName(pTabName) {}
		std::string tabName;
		std::string buttonName;
	};

	std::vector<Tab> tabs;
	
	std::string groupName;
	std::string button_bar;

	utl::Direction dir = utl::Direction::up;
};

#endif // TABBAR_H
