#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <stack>

#include "QuestiaEng/StateManager/State.h"

class Engine;

class StateManager
{
public:
    StateManager(Engine& eng);
    ~StateManager();

    void createState(State* state);
    void deleteState();
    void changeState(State* state);

    void processImputState(sf::Keyboard::Key key, bool isPressed);
    void updateState();
    void displayTexturesState();

private:
    std::stack<State*> stateStack;
	
	Engine& eng;
};

#endif // STATEMANAGER_H
