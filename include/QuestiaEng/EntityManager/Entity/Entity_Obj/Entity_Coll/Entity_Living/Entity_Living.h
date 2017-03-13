#ifndef ENTITY_LIVING_H
#define ENTITY_LIVING_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Coll.h"

class Entity_Living : public Entity_Coll
{
public:
    Entity_Living(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds collBounds, Bounds hitBounds, utl::Vector2f origin);
    virtual ~Entity_Living() = 0;

    int hp = 0;
    int mp = 0;
    int st = 0;

    void processInput();
private:
};

#endif // ENTITY_LIVING_H
