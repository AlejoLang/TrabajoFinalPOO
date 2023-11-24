#include <SFML/Graphics.hpp>
#include "Entity.h"

Entity::Entity() {
}

void Entity::setTexture(sf::Texture &entityTexture) {
  entityTexture.setSmooth(true);
  entitySprite.setTexture(entityTexture);
  entitySprite.setOrigin((sf::Vector2f)entityTexture.getSize() / 2.0f);
}

void Entity::drawIn(sf::RenderWindow &window) {
  window.draw(entitySprite);
}
