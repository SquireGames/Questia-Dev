#ifndef ENTITY_OBJ_H
#define ENTITY_OBJ_H

#include "QuestiaEng/EntityManager/Entity/Entity.h"

#include "QuestiaEng/Utl/Type/Vector2.h"

enum class pKey {};
union pValue
{
	int i;
	unsigned int ui;
	float f;
};

class Entity_Obj : public Entity
{
public:
	Entity_Obj(unsigned int id, EntityManager& entityManager, ResourceManager* resourceManager, utl::Vector2f coords);
	virtual ~Entity_Obj() = 0;

	virtual void update() = 0;

	virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer) = 0;
	//distance between coords and ground
	virtual int getGroundOffset() = 0;


	utl::Vector2f coords;
	std::string displayTag;
	//distance between coords and tag text display
	int tagOffset = -16;
	bool showTag = false;

protected:
	virtual void defaultUses() override;

	std::map<pKey, pValue> properties;
	ResourceManager* resourceManager;
};

#endif // ENTITY_OBJ_
