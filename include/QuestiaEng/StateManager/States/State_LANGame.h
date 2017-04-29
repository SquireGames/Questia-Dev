#ifndef STATE_GAME_H
#define STATE_GAME_H
/*

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <sstream>

#include "QuestiaEng/StateManager/State.h"

#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/EntityManager/EntityManager.h"

#include "QuestiaEng/Data/Data_Desktop.h"

class State_LANGame : public State
{
public:
    State_LANGame(sf::RenderWindow &mWindow);
    ~State_LANGame();

    void processInput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    sf::Vector2f player_Velocity;
    sf::Vector2f player_Coordinates;
    sf::Vector2f player_MapCoordinates;

    sf::View gameView;
    sf::View overlayView;

    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;

    sf::RenderWindow& window;

    TileEngine tileEngine;
    EntityManager entityManager;

    sf::Text mStatisticsText;
    sf::Text mStatisticsText2;

    sf::Text statisticsTextHP;
    sf::Text statisticsTextMP;
    sf::Text statisticsTextStamina;

    sf::Text statisticsTextEntityCount;

    sf::Font gameFont;
    std::ostringstream os;

    int tempCoords_x, tempCoords_y;
};
*/

#endif // STATE_GAME_H
