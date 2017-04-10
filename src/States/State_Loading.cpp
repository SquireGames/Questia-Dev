#include "QuestiaDev/States/State_Loading.h"

State_Loading::State_Loading()
{

}

State_Loading::~State_Loading()
{
	
}

void State_Loading::init()
{
	loadSprite.setTexture(eng->res().getTexture("Media/Image/Game/Entity/Goblin/Hostile/hostile_goblin.png"));
	loadSprite.setPosition(100, 100);
}
void State_Loading::processImput(sf::Keyboard::Key key, bool isPressed)
{

}
void State_Loading::update(sf::Time elapsedTime)
{
	loadSprite.rotate(angle++);
}

void State_Loading::displayTextures()
{
	eng->win().draw(loadSprite);
}
