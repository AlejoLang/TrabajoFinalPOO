#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Asteroid : public Entity {
  private:
    sf::Vector2f asteroidVelocity;
    sf::CircleShape asteroidCollisionBox;
  public:
    Asteroid(sf::Texture &astText, sf::View &view);
    sf::CircleShape getCollisionBox();
    bool checkCollisionWithObject(sf::Sprite &sprite);
    void update();
};

#endif