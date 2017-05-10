#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include <string>

#include "QuestiaEng/Utl/Controls/MouseListener.h"

class GuiElement
{
public:
	GuiElement() = default;
	~GuiElement() = default;

	virtual void update(MouseListener& mouse);
	virtual void handleInput(std::u32string& input); 
};

#endif // GUIELEMENT_H
