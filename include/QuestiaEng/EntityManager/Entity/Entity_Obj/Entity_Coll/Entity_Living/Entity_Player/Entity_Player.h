#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Living/Entity_Living.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Controls/KeyAction.h"
#include "QuestiaEng/Utl/SpriteSheet.h"

#define PLR_SIZE_X 45*2
#define PLR_SIZE_Y 70*2

enum class MovementControl
{
    inControl = 0, skillControl = 1, hybridControl = 2, noMovement = 3
};

class Entity_Player : public Entity_Living
{
public:
    Entity_Player(unsigned int id, EntityManager& entityManager, ResourceManager* resourceManager, utl::Vector2f coords);
    virtual ~Entity_Player() = 0;
	
	virtual void update() = 0;
	
	virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer) = 0;
	//distance between coords and ground
	virtual int getGroundOffset() = 0;

	virtual const Bounds* getCollBounds() = 0;
	virtual const Bounds* getHitBounds() = 0;

private:
	virtual void defaultUses() override final;
	
	virtual void onCollision(const std::map<pKey, pValue>& atrs, unsigned int entityID) = 0;
};

#endif // ENTITY_PLAYER_H
