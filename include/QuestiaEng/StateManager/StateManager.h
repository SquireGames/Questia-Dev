#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <iostream>
#include <stack>

#include "QuestiaEng/StateManager/State.h"

class StateManager
{
public:
    StateManager();
    ~StateManager();

    static StateManager& getInstance();

    void createState(State* state);
    void deleteState();
    void changeState(State* state);

    void processImputState(sf::Keyboard::Key key, bool isPressed);
    void updateState(sf::Time elapsedTime);
    void displayTexturesState();

private:
    std::stack<State*> stateStack;
};

#endif // STATEMANAGER_H
