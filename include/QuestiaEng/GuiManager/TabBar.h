#ifndef TABBAR_H
#define TABBAR_H

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"
#include "QuestiaEng/GuiManager/MenuStack.h"

class TabBar : public GuiElement
{
public:
	TabBar(utl::Direction direction);
	~TabBar();

	int addTab(std::string text);
	void addEntry(int tabID, std::string entryText, std::string buttonName);
	void addEntry(std::string entryText, std::string buttonName);
	void init(std::string tabBarName, GuiManager& pGuiManager, GuiLoader& guiLoader);

	//automatically called if MenuStack is registered into GuiHandler
	void update(MouseListener& mouse);

	void setActivity(bool isActive);
	bool isActive() {return isTabBarActive;}

private:
	GuiManager* guiManager;

	bool isTabBarActive = true;
	int mostRecentTab = 0;

	struct Tab
	{
		Tab(std::string pTabName, utl::Direction dir):tabName(pTabName), menu((dir == utl::Direction::down) ? utl::Direction::up : utl::Direction::down) {}
		std::string tabName;
		std::string buttonName;
		MenuStack menu;
	};

	std::vector<Tab> tabs;

	std::string groupName;
	std::string button_bar;

	utl::Direction dir = utl::Direction::up;
};

#endif // TABBAR_H
