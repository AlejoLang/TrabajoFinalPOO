#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

class Airplane : public Obstacle {
  public:
    Airplane(std::vector<sf::Texture> &planeTexures, sf::View &view);
    ~Airplane() {};
};