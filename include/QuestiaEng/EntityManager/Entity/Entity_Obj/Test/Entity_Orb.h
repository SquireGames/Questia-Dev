#ifndef ENTITY_ORB_H
#define ENTITY_ORB_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Obj.h"

#define SIZE_X 50
#define SIZE_Y 50

class Entity_Orb : public Entity_Obj
{
public:
    Entity_Orb(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, utl::Vector2f _coords);
    ~Entity_Orb();

    void update();
    void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

private:
    sf::Sprite sprite;
};

#endif // ENTITY_ORB_H
