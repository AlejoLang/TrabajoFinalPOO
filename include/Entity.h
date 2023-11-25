#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <string>

class Entity {
  protected:
    sf::Sprite entitySprite;
    sf::Texture entityTexture;
  public:
    Entity();
    void drawIn(sf::RenderWindow &window);
    void setTexture(sf::Texture &entityTexture);
    sf::Vector2f getCenter();
};

#endif