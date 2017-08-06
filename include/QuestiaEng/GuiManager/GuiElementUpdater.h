#ifndef GUIELEMENTUPDATER_H
#define GUIELEMENTUPDATER_H

#include <string>

#include "QuestiaEng/GuiManager/GuiElement/GuiElement.h"
#include "QuestiaEng/GuiManager/GuiElement/TabBar.h"

class GuiElementUpdater
{
public:
	GuiElementUpdater(MouseListener& mouse);
	~GuiElementUpdater();

	void regMouseUpdates(GuiElement* guiElement);
	void regTextUpdates(GuiElement* guiElement);
	void update(std::u32string& input);
	void clear();

private:
	MouseListener& mouse;

	std::vector<GuiElement*> elements;
	std::vector<GuiElement*> inputs;
};

#endif // GUIELEMENTUPDATER_H
