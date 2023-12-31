#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"

class Game;

class Scene {
  protected:
    sf::Font* sceneFont;
  public:
    Scene(sf::Font* font) : sceneFont(font) {};
    virtual void update(Game &game, sf::RenderWindow &window) = 0;
    virtual void drawIn(sf::RenderWindow &window) = 0;
};

#endif