#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <string>

#include "QuestiaEng/GuiManager/GuiElement.h"
#include "QuestiaEng/GuiManager/TabBar.h"

class GuiHandler
{
public:
	GuiHandler(MouseListener& mou);
	~GuiHandler();

	void reg(GuiElement* guiElement);
	void update();
	void clear();

private:
	MouseListener& mouse;

	std::vector<GuiElement*> elements;
};

#endif // GUIHANDLER_H
