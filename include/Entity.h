#pragma once
#include <SFML/Graphics.hpp>

class Entity {
  protected:
    sf::Sprite entitySprite;
    sf::Texture entityTexture;
  public:
    Entity() {};
    Entity(sf::Texture &texture);
    virtual void drawIn(sf::RenderWindow &window);
    void setTexture(sf::Texture &texture);
    bool collides(sf::Sprite &sprite);
    sf::Vector2f getCenter();
    sf::Sprite& getSprite();
    virtual ~Entity() {};
};