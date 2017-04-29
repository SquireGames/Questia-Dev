#ifndef STATE_CHARACTERSELECTION_H
#define STATE_CHARACTERSELECTION_H

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/Utl/SaveFile.h"

class State_CharacterSelection : public State
{
public:
    State_CharacterSelection(sf::RenderWindow &window);
    ~State_CharacterSelection();

    void processInput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;
};

#endif // STATE_CHARACTERSELECTION_H
