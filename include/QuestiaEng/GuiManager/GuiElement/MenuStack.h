#ifndef MENUSTACK_H
#define MENUSTACK_H

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiElement/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

class MenuStack : public GuiElement
{
public:
	MenuStack(utl::Direction direction);
	~MenuStack();

	int addEntry(const std::string& text, const std::string& buttonName);
	void init(const std::string& stackName, int x, int y, GuiManager& guiManager, GuiLoader& guiLoader);
	
	unsigned int size() {return entries.size();}
	
	void handleInput(std::u32string& input);
	
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
		Entry(const std::string& entryText):entryText(entryText) {}
		std::string entryText;
		std::string buttonName;
		//TODO make possible boolean toggle
	};
	std::vector<Entry> entries;

	std::string listName;

	utl::Direction dir = utl::Direction::down;
};

#endif // MENUSTACK_H
