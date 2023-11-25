#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>

Ship::Ship () {
  entitySprite.setPosition(200, 200);
  fuel = 100;
  acceleration = 0;
  gravityAcceleration = 0;
}

void Ship::update() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && fuel > 0) {
    entitySprite.rotate(-0.5);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && fuel > 0) {
    entitySprite.rotate(0.5);
  }
  velocity = calculateDirection();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuel > 0) {
    fuel -= 0;
    acceleration += 0.2;
    entitySprite.rotate(velocity.x * 0.5);
  }
  acceleration -= 0.1;
  gravityAcceleration += 0.135;
  gravityAcceleration > 10 ? gravityAcceleration = 10 : gravityAcceleration = gravityAcceleration;
  acceleration < 0 ? acceleration = 0 : acceleration = acceleration;
  velocity *= acceleration;
  velocity.y += gravityAcceleration;
  entitySprite.move(velocity);
}

sf::Vector2f Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  return direction;
}