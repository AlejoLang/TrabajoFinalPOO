#include <SFML/Graphics.hpp>
#include "Entity.h"

Entity::Entity(sf::Texture &texture){
  entitySprite.setTexture(texture);
  entitySprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
  collisionBox.setSize({texture.getSize().x, texture.getSize().y});
  collisionBox.setOrigin(collisionBox.getSize() / 2.0f);
  collisionBox.setPosition(entitySprite.getPosition());
}

void Entity::drawIn(sf::RenderWindow &window) {
  window.draw(entitySprite);
}

sf::Vector2f Entity::getCenter() {
  return entitySprite.getPosition();
}

sf::RectangleShape Entity::getCollisionBox() {
  return this->collisionBox;
}