#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>

class Scene {
  public:
    virtual void update() = 0;
    virtual void drawIn(sf::RenderWindow &window) = 0;
};

#endif