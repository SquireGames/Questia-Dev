#ifndef ENTITY_CRATE_H
#define ENTITY_CRATE_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Coll.h"

#define SIZE_X 50
#define SIZE_Y 50

class Entity_Crate : public Entity_Coll
{
public:
    Entity_Crate(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, const utl::Vector2f& _coords);
    ~Entity_Crate();

    void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

private:
    sf::Sprite sprite;

    void onCollision(std::map <Type, Type_Field>& atrs, const unsigned int& entityID);
};

#endif // ENTITY_CRATE_H
