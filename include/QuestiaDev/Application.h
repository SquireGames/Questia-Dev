#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "QuestiaEng/Data/InputBuffer.h"

#include "QuestiaEng/Data/Data_Desktop.h"

#include "QuestiaEng/Utl/SaveFile/SaveFile_Options.h"

#include "QuestiaEng/StateManager/StateManager.h"
#include "QuestiaEng/StateManager/States/State_Transition.h"


class Application
{
public:
    Application();
    ~Application();
    void run();

private:
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void processEvents();
    void update(sf::Time elapsedTime);
    void updateStatistics(sf::Time elapsedTime);
    void render();
	
	InputBuffer inputBuffer;

    sf::RenderWindow window_main;
    SaveFile_Options saveFile;
    const sf::Time timePerFrame = sf::seconds(1.f / 128.f);

    sf::Time mStatisticsUpdateTime;
    int mStatisticsFramesCount;
};
#endif // APPLICATION_H
