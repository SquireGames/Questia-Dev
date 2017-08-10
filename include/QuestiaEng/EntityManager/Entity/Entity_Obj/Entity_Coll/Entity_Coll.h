#ifndef ENTITY_COLL_H
#define ENTITY_COLL_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Obj.h"
#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Bounds.h"

class Entity_Coll : public Entity_Obj
{
public:
	Entity_Coll(unsigned int id, EntityManager& entityManager, ResourceManager* resourceManager, utl::Vector2f coords);
	virtual ~Entity_Coll() = 0;

	virtual void update() = 0;
	
	virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer) = 0;
	//distance between coords and ground
	virtual int getGroundOffset() = 0;
 

	void attemptMove(utl::Vector2f velocity);
	void forceMove(utl::Vector2f velocity);

	virtual const Bounds* getCollBounds() = 0;
	virtual const Bounds* getHitBounds() = 0;

	bool isPermeable = true;
	bool isSolid     = true;
	
	//called externally
	void onCollision(Entity_Coll& other);

protected:
	virtual void defaultUses() override;

	virtual void onCollision(const std::map<pKey, pValue>& atrs, unsigned int entityID) = 0;
};

#endif // ENTITY_COLL_H
