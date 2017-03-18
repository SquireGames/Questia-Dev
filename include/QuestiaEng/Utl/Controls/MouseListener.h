#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <iostream>
#include "SFML/Window/Mouse.hpp"
#include "QuestiaEng/Utl/Controls/Input.h"

class MouseListener
{
public:
    MouseListener();

    void update();
    bool isMouseHeld(ctr::Input button);
    bool isMousePressed(ctr::Input button);
    bool isMouseReleased(ctr::Input button);

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
};

#endif // MOUSELISTENER_H
