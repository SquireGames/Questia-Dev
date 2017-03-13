#ifndef STATE_TRANSITION_H
#define STATE_TRANSITION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "QuestiaEng/StateManager/StateManager.h"
#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/StateManager/States/State_Transition.h"

#include "QuestiaEng/StateManager/States/State_MainMenu.h"
#include "QuestiaEng/StateManager/States/State_Game.h"
#include "QuestiaEng/StateManager/States/State_OptionsMenu/State_OptionsMenu.h"
#include "QuestiaEng/StateManager/States/State_CharacterSelection.h"
#include "QuestiaEng/StateManager/States/State_TileMapEditor.h"
#include "QuestiaEng/StateManager/States/State_MapSelector.h"
#include "QuestiaEng/StateManager/States/State_MultiplayerGame.h"
#include "QuestiaEng/StateManager/States/State_MultiplayerSelection.h"

enum class GameState
{
    State_MainMenu             = 1,
    State_Game                 = 2,
    State_OptionsMenu          = 3,
    State_CharacterSelection   = 4,
    State_TileMapEditor        = 5,
    State_MapSelector          = 6,
    State_MultiplayerGame      = 7,
    State_MultiplayerSelection = 8
};

class State_Transition : public State
{
public:
    State_Transition(sf::RenderWindow& window, int _stateID);
    State_Transition(sf::RenderWindow& window, GameState _stateID);
    ~State_Transition();

    void processImput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::RenderWindow& window;

    int stateID;

    sf::Texture aLoadingTexture;
    sf::Sprite aLoadingImage;
};

#endif // STATE_TRANSITION_H


