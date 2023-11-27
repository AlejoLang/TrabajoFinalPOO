#ifndef ASTEROID_H
#define ASTEROID_H
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Asteroid : public Entity {
  private:
    sf::Vector2f asteroidVelocity;
  public:
    Asteroid(sf::Texture &astText, sf::View &view);
    void update();
};

#endif