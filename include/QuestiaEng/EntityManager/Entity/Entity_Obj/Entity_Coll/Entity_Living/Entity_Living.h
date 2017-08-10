#ifndef ENTITY_LIVING_H
#define ENTITY_LIVING_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Coll.h"

class Entity_Living : public Entity_Coll
{
public:
	Entity_Living(unsigned int id, EntityManager& entityManager, ResourceManager* resourceManager, utl::Vector2f coords);
	virtual ~Entity_Living() = 0;

	virtual void update() = 0;
	
	virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer) = 0;
	//distance between coords and ground
	virtual int getGroundOffset() = 0;

	virtual const Bounds* getCollBounds() = 0;
	virtual const Bounds* getHitBounds() = 0;


	int hp = 0;
	int mp = 0;
	int st = 0;

protected:
	virtual void defaultUses() override;
	
	virtual void onCollision(const std::map<pKey, pValue>& atrs, unsigned int entityID) = 0;
};

#endif // ENTITY_LIVING_H
