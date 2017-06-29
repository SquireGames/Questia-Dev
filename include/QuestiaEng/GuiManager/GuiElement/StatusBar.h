#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/GuiManager/GuiLoader.h"

#include "QuestiaEng/Utl/Utl.h"

#include "GuiElement.h" //Base class: GuiElement

class StatusBar : public GuiElement
{
public:
	StatusBar(utl::Direction direction = utl::Direction::down, int offset = 0);
	~StatusBar();

	void track(const std::string& text, int val, int space);
	void track(const std::string&, const std::string&, int space);
	void addSpace(int space);

	void init(const std::string& barName, GuiManager& guiManager, GuiLoader& guiLoader);

	void updateVal(const std::string&, int val);
	void updateVal(const std::string&, const std::string&);

	//GuiElement
	void update(MouseListener& mouse);

	void setActivity(bool isActive);
	bool isActive() {return isBarActive;}
	bool isHovered() {return isBarHovered && isBarActive;}

private:
	GuiManager* guiManager;

	utl::Direction dir;
	int offset_y;

	struct Entry
	{
		std::string key;
		std::string atrName_key;
		std::string atrName_val;
		int spacing;
	};

	std::vector<Entry> entries;

	bool isBarActive = true;
	bool isBarHovered = false;

	std::string buttonName;
};

#endif // STATUSBAR_H
