#ifndef ENTITY_H
#define ENTITY_H

#include "QuestiaEng/EntityManager/EntityManager.h"

//forward declarations for used functions
class Entity_Obj;
class Entity_Coll;
class Entity_Living;
class Entity_Player;

class Entity
{
public:
    Entity(unsigned int id, EntityManager& entityManager);
    virtual ~Entity() = 0;

    virtual void update() = 0;

    unsigned int getID();

protected:
	virtual void defaultUses();
	void useUpdate(Entity* e);
	void useObj(Entity_Obj* e);
	void useColl(Entity_Coll* e);
	void useLiving(Entity_Living* e);
	void usePlayer(Entity_Player* e);
	
    EntityManager& entityManager;

private:
    unsigned int id;
	
	friend class EntityManager;
	
	bool inEntity_Base 	 = false;
	bool inEntity_Obj 	 = false;
	bool inEntity_Coll 	 = false;
	bool inEntity_Living = false;
	bool inEntity_Player = false;
};

#endif // ENTITY_H
