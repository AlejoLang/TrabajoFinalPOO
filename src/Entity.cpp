#include <SFML/Graphics.hpp>
#include "Entity.h"

Entity::Entity(sf::Texture &texture){
  entitySprite.setTexture(texture);
  entitySprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}

void Entity::drawIn(sf::RenderWindow &window) {
  window.draw(entitySprite);
}

bool Entity::collides(sf::Sprite &sprite) {
  return Collision::pixelPerfectTest(entitySprite, sprite);
}

sf::Vector2f Entity::getCenter() {
  return entitySprite.getPosition();
}

sf::Sprite& Entity::getSprite() {
  return this->entitySprite;
}