#ifndef ENTITY_PLAYER_H
#define ENTITY_PLAYER_H

#include "QuestiaEng/EntityManager/Entity/Entity_Obj/Entity_Coll/Entity_Living/Entity_Living.h"

#include "QuestiaEng/Utl/Utl.h"
#include "QuestiaEng/Utl/Controls/KeyAction.h"
#include "QuestiaEng/Utl/SpriteSheet.h"

#define SIZE_X 45*2
#define SIZE_Y 70*2

enum class MovementControl
{
    inControl = 0, skillControl = 1, hybridControl = 2, noMovement = 3
};

class Entity_Player : public Entity_Living
{
public:
    Entity_Player(unsigned int id, EntityManager& entityManager, ResourceManager& resourceManager);
    ~Entity_Player();

    void processInput(ctr::KeyAction action, bool isPressed);
    void mouseInput(utl::Vector2f mousePosition);
    void update();
    void draw(sf::RenderWindow& window, const DrawLayer& drawLayer);

    //movement
    MovementControl mov_control = MovementControl::inControl;
    std::vector<utl::Vector2f> mov_forces_external;
    float mov_speedBase = 2.5;
    float mov_speedModifier = 0;
    float mov_speedMultiplier = 1;

    utl::Direction facingDirection = utl::Direction::up;

    utl::Vector2f attackOrigin = utl::Vector2f(0,0);

    int exp_general = 0;
private:
    SpriteSheet spriteSheet;
    utl::Vector2ui spriteSheetIndex = utl::Vector2ui(0,0);

    bool isMovingUp    = false;
    bool isMovingDown  = false;
    bool isMovingLeft  = false;
    bool isMovingRight = false;
};

#endif // ENTITY_PLAYER_H
