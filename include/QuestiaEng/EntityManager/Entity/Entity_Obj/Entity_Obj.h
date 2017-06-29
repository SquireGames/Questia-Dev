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
    Entity_Obj(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager, utl::Vector2f coords);
    virtual ~Entity_Obj() = 0;

    virtual void draw(sf::RenderWindow& window, DrawLayer drawLayer);
	//distance between coords and ground
	virtual int getGroundOffset();

    utl::Vector2f coords;
	
	std::string displayTag = std::string();
	bool showTag = false;
	//distance between coords and tag text display
	int tagOffset = -16;
	
protected:
	std::map<pKey, pValue> properties;
	
    ResourceManager& resourceManager;
};

#endif // ENTITY_OBJ_
