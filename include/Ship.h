#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include "Asteroid.h"

class Ship : public Entity {
  private:
    sf::Vector2f velocity;
    float acceleration;
    float gravityAcceleration;
    float fuelLOX;
    float fuelCH4;
    float altitudKm;
    float angularMomentum;
  public:
    Ship(sf::Texture &playerTexture, Map &mainMap, sf::RenderWindow &window);
    void update(Map &mainMap);
    void handleTrust();
    void handleRotation();
    void handleGravity(Map &mainMap);
    void calculateDirection();
    void increaseLOX(float val);
    void increaseCH4(float val);
    float getLOX();
    float getCH4();
    float getAltitude();
};

#endif