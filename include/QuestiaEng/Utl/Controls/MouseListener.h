#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <iostream>
#include "SFML/Window/Mouse.hpp"
#include "QuestiaEng/Utl/Controls/Input.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

class MouseListener
{
public:
    MouseListener();

    void update();
	void setScroll(int newScroll) {scroll = newScroll;}
	void setMousePos(utl::Vector2f newMousePos){mousePos = newMousePos;}
	
    bool isMouseHeld(ctr::Input button);
    bool isMousePressed(ctr::Input button);
    bool isMouseReleased(ctr::Input button);
	int getScroll(){return scroll;}
	utl::Vector2f getMousePos(){return mousePos;}
	
	
private:
    bool isMouseHeld_l = false;
    bool isMouseHeld_m = false;
    bool isMouseHeld_r = false;
    bool isMouseHeld_1 = false;
    bool isMouseHeld_2 = false;
    bool isMouseReleased_l = false;
    bool isMouseReleased_m = false;
    bool isMouseReleased_r = false;
    bool isMouseReleased_1 = false;
    bool isMouseReleased_2 = false;
    bool isMousePressed_l = false;
    bool isMousePressed_m = false;
    bool isMousePressed_r = false;
    bool isMousePressed_1 = false;
    bool isMousePressed_2 = false;
	
	int scroll = 0;
	
	utl::Vector2f mousePos;
};

#endif // MOUSELISTENER_H
