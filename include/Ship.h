#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"

class Ship : public Entity {
  private:
    sf::Vector2f velocity;
    float acceleration;
    float gravityAcceleration;
    float fuel;
  public:
    Ship();
    void update(Map &mainMap);
    sf::Vector2f calculateDirection();
};

#endif