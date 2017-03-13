#ifndef ENTITY_H
#define ENTITY_H

#include "QuestiaEng/EntityManager/EntityManager.h"

class Entity
{
public:
    Entity(unsigned int _id, EntityManager& _entityManager);
    virtual ~Entity() = 0;

    virtual void update();

    unsigned int getID();

protected:
    EntityManager& entityManager;

private:
    unsigned int id;
};

#endif // ENTITY_H
