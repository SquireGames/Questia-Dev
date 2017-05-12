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

	int addEntry(std::string text, std::string buttonName);
	void init(std::string stackName, int x, int y, GuiManager& pGuiManager, GuiLoader& guiLoader);
	
	void handleInput(std::u32string& input);
	//automatically called if MenuStack is registered into GuiHandler
	void update(MouseListener& mouse);
	
	void setActivity(bool active);
	bool isActive();

private:
	GuiManager* guiManager;
	bool isStackActive = false;
	//makes menuStack hide next tick
	bool toHide = false;

	struct Entry
	{
		Entry(std::string pEntryText):entryText(pEntryText) {}
		std::string entryText;
		std::string buttonName;
		//TODO make possible boolean toggle
	};
	std::vector<Entry> entries;

	std::string listName;

	utl::Direction dir = utl::Direction::down;
};

#endif // MENUSTACK_H
