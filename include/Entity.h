#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Collision.h"

class Entity {
  protected:
    sf::Sprite entitySprite;
    sf::Texture entityTexture;
  public:
    Entity(sf::Texture &texture);
    virtual void drawIn(sf::RenderWindow &window);
    bool collides(sf::Sprite &sprite);
    sf::Vector2f getCenter();
    sf::Sprite& getSprite();
};

#endif