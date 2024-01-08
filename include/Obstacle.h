#pragma once 
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Obstacle : public Entity {
  protected:
    sf::Vector2f obstacleVelocity;
  public:
    Obstacle() : Entity() {};
    void update() { entitySprite.move(obstacleVelocity); };
    virtual ~Obstacle() {};
};