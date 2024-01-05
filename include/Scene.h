#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

class Game;

class Scene {
  protected:
    sf::Font* sceneFont;
    sf::Event sceneEvent;
  public:
    Scene(sf::Font* font) : sceneFont(font) {};
    virtual void update(Game &game, sf::RenderWindow &window) = 0;
    virtual void processEvent(sf::Event &ev) = 0;
    virtual void drawIn(sf::RenderWindow &window) = 0;
    ~Scene() {};
};