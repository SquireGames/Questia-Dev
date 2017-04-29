#ifndef STATE_GAME_H
#define STATE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "QuestiaEng/StateManager/StateManager.h"
#include "QuestiaEng/StateManager/State.h"
#include "QuestiaEng/StateManager/States/State_Transition.h"

#include "QuestiaEng/TileEngine/TileEngine.h"
#include "QuestiaEng/EntityManager/EntityManager.h"
#include "QuestiaEng/GuiManager/GuiManager.h"
#include "QuestiaEng/ResourceManager/ResourceManager.h"
#include "QuestiaEng/MultiplayerManager/MultiplayerManager.h"

#include "QuestiaEng/GuiManager/GuiLoader.h"

#include "QuestiaEng/Utl/SaveFile.h"
#include "QuestiaEng/SaveFile_Options.h"
#include "QuestiaEng/Data/Data_Desktop.h"

#include "QuestiaEng/Utl/Threads/ThreadPool_Fixed.h"

#include "QuestiaEng/Identifiers/DrawLayer.h"

#include "QuestiaEng/Utl/Controls/KeyAction.h"

//temp
#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Living/Entity_Player/Entity_Player.h"

class State_Game : public State
{
public:
    State_Game(sf::RenderWindow &window);
    ~State_Game();

    void processInput(sf::Keyboard::Key key,bool isPressed);
    void update(sf::Time elapsedTime);
    void displayTextures();

private:
    SaveFile_Options saveFile;

    sf::View gameView;
    sf::View overlayView;

    sf::RenderWindow& window;

    ResourceManager resourceManager;
    GuiManager guiManager;
    GuiLoader guiLoader;

    TileEngine tileEngine;
    EntityManager entityManager;

    bool paused = false;
    bool showColl = true;

    ThreadPool_Fixed threadPool;

    //tasks
    void gameLogic();
    void task_lighting();
    void task_ai();
    void task_particles();
    void task_gui();

    //keys
    ctr::Input ctr_moveUp;
    ctr::Input ctr_moveDown;
    ctr::Input ctr_moveLeft;
    ctr::Input ctr_moveRight;
    ctr::Input ctr_skill_1;
    ctr::Input ctr_skill_2;
    ctr::Input ctr_skill_3;
    ctr::Input ctr_skill_4;
    ctr::Input ctr_skill_5;
    ctr::Input ctr_skill_6;

    //TEMP
    sf::Sprite alignment;
    sf::Sprite alignment2;
    sf::VertexArray visibleScreen;

};

#endif // STATE_GAME_H
