#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>

Ship::Ship () {
  entitySprite.setPosition(200, 200);
  fuel = 100;
  acceleration = 0;
  gravityAcceleration = 0;
  velocity = {0, 0};
}

void Ship::update(Map &mainMap) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuel > 0) {
    fuel -= 0;
    acceleration += 0.3;
    gravityAcceleration -= 0.2;
    entitySprite.rotate(velocity.x / acceleration / 2);
  }
  acceleration -= 0.2;
  acceleration < 0 ? acceleration = 0 : acceleration = acceleration;
  velocity -= {velocity.x - acceleration, velocity.y - acceleration};
  velocity = {velocity.x * calculateDirection().x, velocity.y * calculateDirection().y};

  if(!mainMap.checkCollision(entitySprite)) {
    gravityAcceleration += 0.135;
    gravityAcceleration > 100 ? gravityAcceleration = 100 : gravityAcceleration = gravityAcceleration;
    velocity.y += gravityAcceleration;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && fuel > 0) {
      entitySprite.rotate(-0.5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && fuel > 0) {
      entitySprite.rotate(0.5);
    }
  } else {
  }
  entitySprite.move(velocity);
}

sf::Vector2f Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  return direction;
}
