#ifndef STATE_MAPSELECTOR_H
#define STATE_MAPSELECTOR_H

#include <SFML/Graphics.hpp>

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/Data/Data_Desktop.h"

class State_MapSelector : public State
{
public:
    State_MapSelector(sf::RenderWindow &window);
    ~State_MapSelector();

    void processInput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;
};

#endif // STATE_MAPSELECTOR_H
