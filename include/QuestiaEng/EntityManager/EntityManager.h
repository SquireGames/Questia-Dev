#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <list>
#include <memory> //std::shared_ptr
#include <cmath> //std::fabs()

#include <iostream>

#include <SFML/Graphics.hpp>

#include "QuestiaEng/ResourceManager/ResourceManager.h"

#include "QuestiaEng/Identifiers/DrawLayer.h"

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Bounds.h"

#include "QuestiaEng/Utl/Type/Rect.h"

//forward declarations
class Entity;
class Entity_Obj;
class Entity_Coll;
class Entity_Living;
class Entity_Player;

class EntityManager
{
public:
	EntityManager(ResourceManager& resourceManager, sf::RenderWindow& window);
	~EntityManager();

	//registers recipes of entities
	void reg(const std::string& name, std::function<Entity*(unsigned int id, EntityManager&)> entity);
	void reg(const std::string& name, std::function<Entity*(unsigned int id, EntityManager&, ResourceManager&, utl::Vector2f coords)> entity);

	//spawns registered entities
	int spawn(const std::string& name);
	int spawn(const std::string& name, utl::Vector2f pos);

	void update();

	void draw(DrawLayer drawLayer);
	void draw_coll();

	Entity_Player& getPlayer(unsigned int playerID);

	//used by entities
	void queueKill(unsigned int id);
	void attemptMove(Entity_Coll& entity, const utl::Vector2f& velocity);

private:
	ResourceManager& resourceManager;
	sf::RenderWindow& window;

	//every entity has a unique ID
	unsigned int idCounter = 0;
	unsigned int getNewID();
	std::list <unsigned int> ids;
	std::vector <unsigned int> deadIDs;

	//holds recipes for entities
	std::map<std::string, std::function<Entity*(unsigned int id, EntityManager&)>> entityRegistry;
	std::map<std::string, std::function<Entity*(unsigned int id, EntityManager&, ResourceManager&, utl::Vector2f coords)>> entityRegistry_Obj;

	//holds every entity
	std::vector<std::unique_ptr<Entity> > entities;

	//only holds entities that use the inherited properties
	std::vector<Entity*>        entities_Base;
	std::vector<Entity_Obj*>    entities_Obj;
	std::vector<Entity_Coll*>   entities_Coll;
	std::vector<Entity_Living*> entities_Living;
	std::vector<Entity_Player*> entities_Player;

	//helpers
	void killEntity(unsigned int id);
	template <class T> void removeID(unsigned int id, std::vector<T>& entityVector);
	void drawCollBounds(sf::RenderWindow& window, const Bounds* bounds, utl::Vector2f coords, sf::Color color);
	Entity* getEntity(unsigned int id);
	
	friend class Entity;
};

template <class T>
void EntityManager::removeID(unsigned int id, std::vector<T>& entityVector)
{
	auto iter = entityVector.end();
	for(auto it = entityVector.begin(); it != entityVector.end(); it++)
	{
		if(id == (*it)->getID())
		{
			iter = it;
			break;
		}
	}
	if(iter != entityVector.end())
	{
		entityVector.erase(iter);
	}
}

#endif // ENTITYMANAGER_H
