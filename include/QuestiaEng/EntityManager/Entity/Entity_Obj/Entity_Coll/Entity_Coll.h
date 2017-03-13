#ifndef ENTITY_COLL_H
#define ENTITY_COLL_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Obj.h"
#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Bounds.h"

class Entity_Coll : public Entity_Obj
{
public:
    Entity_Coll(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, Bounds _bounds, Bounds _hitBounds, utl::Vector2f origin);

    virtual ~Entity_Coll() = 0;

    void attemptMove(Entity_Coll& entity, const utl::Vector2f velocity);
    void forceMove(Entity_Coll& entity, const utl::Vector2f velocity);

    void onCollision(Entity_Coll& other);

    Bounds collBounds;
    Bounds hitBounds;

    utl::Vector2f previousVelocity = utl::Vector2f(0,0);

    bool isPermeable = true;
    bool isSolid     = true;

protected:
    virtual void onCollision(std::map <Type, Type_Field>& atrs, const unsigned int& entityID);
};

#endif // ENTITY_COLL_H
