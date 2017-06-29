#ifndef ENTITY_COLL_H
#define ENTITY_COLL_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Obj.h"
#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Bounds.h"

class Entity_Coll : public Entity_Obj
{
public:
	Entity_Coll(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, utl::Vector2f coords);

	virtual ~Entity_Coll() = 0;

	void attemptMove(utl::Vector2f velocity);
	void forceMove(utl::Vector2f velocity);

	void onCollision(Entity_Coll& other);

	virtual const Bounds* getCollBounds();
	virtual const Bounds* getHitBounds();

	bool isPermeable = true;
	bool isSolid     = true;

protected:
	virtual void onCollision(const std::map<pKey, pValue>& atrs, unsigned int entityID);
};

#endif // ENTITY_COLL_H
