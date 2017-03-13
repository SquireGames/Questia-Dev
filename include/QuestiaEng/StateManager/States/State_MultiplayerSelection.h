#ifndef STATE_MULTIPLAYERSELECTION_H
#define STATE_MULTIPLAYERSELECTION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/Data/Data_Desktop.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"

class State_MultiplayerSelection : public State
{
public:
    State_MultiplayerSelection(sf::RenderWindow &window);
    ~State_MultiplayerSelection();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    sf::Sprite aMenuImage;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_MULTIPLAYERSELECTION_H
