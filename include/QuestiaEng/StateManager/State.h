#ifndef STATE_H
#define STATE_H

#include <SFML/Window/Keyboard.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>

class State
{
public:
    State();
    virtual ~State();

    virtual void processImput(sf::Keyboard::Key key, bool isPressed) = 0;
    virtual void update(sf::Time elapsedTime) = 0;
    virtual void displayTextures() = 0;
};

#endif // STATE_H
