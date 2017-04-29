#include "QuestiaDev/States/State_Loading.h"

State_Loading::State_Loading()
{

}

State_Loading::~State_Loading()
{

}

void State_Loading::init()
{
	loadSprite.setTexture(eng->res().getTexture("Media/Image/Game/Entity/Test/Orb.png"));
	backSprite.setTexture(eng->res().getTexture("Media/Image/Gui/Menu/BasicLoading.png"));
	loadSprite.setPosition(1820, 980);
	loadSprite.setOrigin(20, 20);
}
void State_Loading::processInput(sf::Keyboard::Key key, bool isPressed)
{

}
void State_Loading::update(sf::Time elapsedTime)
{
	loadSprite.rotate(1);
}

void State_Loading::displayTextures()
{
	eng->win().draw(backSprite);
	eng->win().draw(loadSprite);
}
