#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"

class Game;

class Scene {
  public:
    virtual void update(Game &game, sf::RenderWindow &window) = 0;
    virtual void drawIn(sf::RenderWindow &window) = 0;
};

#endif