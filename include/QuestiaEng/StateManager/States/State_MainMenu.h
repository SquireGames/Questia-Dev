#ifndef STATE_MAINMENU_H
#define STATE_MAINMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>

#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/StateManager/StateManager.h"
#include "QuestiaEng/StateManager/States/State_Transition.h"

#include "QuestiaEng/GuiManager/GuiLoader.h"

#include "QuestiaEng/Data/Data_Desktop.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"

#include "QuestiaEng/SaveFile_Options.h"
#include "QuestiaEng/Utl/SaveFile.h"

#include "QuestiaEng/Utl/Utl.h"

class State_MainMenu : public State
{
public:
    State_MainMenu(sf::RenderWindow &window);
    ~State_MainMenu();

    void processInput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    GuiLoader guiLoader;

    SaveFile_Options saveFile;

    sf::RenderWindow& window;

    sf::SoundBuffer musicBuffer;
    sf::Sound musicSound;

    ResourceManager resourceManager;
    GuiManager guiManager;
};

#endif // STATE_MAINMENU_H
