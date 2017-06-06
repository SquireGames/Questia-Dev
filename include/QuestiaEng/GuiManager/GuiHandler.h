#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include <string>

#include "QuestiaEng/GuiManager/GuiElement/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiElement/TabBar.h"

class GuiHandler
{
public:
	GuiHandler(MouseListener& mouse);
	~GuiHandler();

	void reg(GuiElement* guiElement);
	void regInput(GuiElement* guiElement);
	void update(std::u32string& input);
	void clear();

private:
	MouseListener& mouse;

	std::vector<GuiElement*> elements;
	std::vector<GuiElement*> inputs;
};

#endif // GUIHANDLER_H
