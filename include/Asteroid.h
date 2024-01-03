#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Asteroid : public Obstacle {
  public:
    Asteroid(std::vector<sf::Texture> &asteroidTexures, sf::View &view);
};