#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>

Ship::Ship (sf::RenderWindow &window) {
  entitySprite.setPosition({window.getSize().x / 2.0f, window.getSize().y - 300});
  fuelLOX = 350;
  fuelCH4 = 100;
  acceleration = 0;
  gravityAcceleration = 0;
  velocity = {0, 0};
}

void Ship::update(Map &mainMap) {
  handleTrust();
  calculateDirection();
  handleGravity(mainMap);
  entitySprite.move(velocity);
}

void Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  velocity = {velocity.x * direction.x, velocity.y * direction.y};
}

void Ship::handleTrust() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuelLOX > 0 && fuelCH4 > 0) {
    fuelLOX -= 0.35;
    fuelCH4 -= 0.1;
    acceleration += 0.3;
    entitySprite.rotate(velocity.x / acceleration * 0.5);
  }
  acceleration -= 0.1;
  acceleration = std::max(0.0f, acceleration);
  velocity -= {velocity.x - acceleration, velocity.y - acceleration};
}

void Ship::handleRotation() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && fuelLOX > 0 && fuelCH4 > 0) {
      entitySprite.rotate(-0.5);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && fuelLOX > 0 && fuelCH4 > 0) {
      entitySprite.rotate(0.5);
    }
}

void Ship::handleGravity(Map &mainMap) {
  if(!mainMap.checkCollision(entitySprite)) {
    gravityAcceleration += 0.135;
    gravityAcceleration > 100 ? gravityAcceleration = 100 : gravityAcceleration = gravityAcceleration;
    velocity.y += gravityAcceleration;
    handleRotation();
  } else {
    gravityAcceleration = 0;
    acceleration = 0;
  }
}

float Ship::getCH4() {
  return this->fuelCH4;
}

float Ship::getLOX() {
  return this->fuelLOX;
}

float Ship::getAltitude() {
  return this->altitudKm;
}