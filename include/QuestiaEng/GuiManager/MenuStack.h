#ifndef MENUSTACK_H
#define MENUSTACK_H

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

class MenuStack : public GuiElement
{
public:
	MenuStack(utl::Direction direction);
	~MenuStack();

	int addEntry(std::string text);
	void init(std::string stackName, int x, int y, GuiManager& pGuiManager, GuiLoader& guiLoader);
	
	void handleInput(std::u32string& input);
	//automatically called if MenuStack is registered into GuiHandler
	void update(MouseListener& mouse);

private:
	GuiManager* guiManager;
	bool isTabBarActive = true;

	struct Entry
	{
		Entry(std::string pEntryText):entryText(pEntryText) {}
		std::string entryText;
		std::string buttonName;
	};
	std::vector<Entry> entries;

	std::string listName;

	utl::Direction dir = utl::Direction::down;
};

#endif // MENUSTACK_H
