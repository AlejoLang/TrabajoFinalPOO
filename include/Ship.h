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
    float fuelLOX;
    float fuelCH4;
  public:
    Ship(sf::RenderWindow &window);
    void update(Map &mainMap);
    void handleTrust();
    void handleRotation();
    void handleGravity(Map &mainMap);
    void calculateDirection();
};

#endif