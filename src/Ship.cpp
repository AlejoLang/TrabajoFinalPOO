#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>

Ship::Ship () {
  entitySprite.setPosition(200, 200);
  fuel = 100;
  acceleration = 0.5;
}

void Ship::update() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    entitySprite.rotate(-0.5);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    entitySprite.rotate(0.5);
  }
  velocity = calculateDirection();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    entitySprite.move(velocity);
  }
}

sf::Vector2f Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  return direction;
}