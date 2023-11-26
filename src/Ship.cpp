#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>

Ship::Ship (sf::Texture &playerTexture, sf::RenderWindow &window) : Entity(playerTexture){
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
  collisionBox.setRotation(entitySprite.getRotation());
  collisionBox.setPosition(entitySprite.getPosition());
}

void Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  velocity = {velocity.x * direction.x, velocity.y * direction.y};
}

void Ship::handleTrust() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuelLOX > 0 && fuelCH4 > 0) {
    fuelLOX -= 0.035;
    fuelCH4 -= 0.01;
    acceleration += 0.3;
    angularMomentum += velocity.x / acceleration * 0.25;
  } else {
    acceleration -= 0.5;  
  }
  angularMomentum += velocity.x / 30.0;
  acceleration = std::max(0.0f, std::min(acceleration, 40.0f));
  velocity -= {velocity.x - acceleration, velocity.y - acceleration};
}

void Ship::handleRotation() {
  const float maxRotationSpeed = 2.0;
    float rotationSpeed = angularMomentum / 10.0;

    rotationSpeed = std::min(rotationSpeed, maxRotationSpeed);
    rotationSpeed = std::max(rotationSpeed, -maxRotationSpeed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && fuelLOX > 0 && fuelCH4 > 0) {
        rotationSpeed -= 0.5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && fuelLOX > 0 && fuelCH4 > 0) {
        rotationSpeed += 0.5;
    }

    entitySprite.rotate(rotationSpeed);
    angularMomentum *= 0.1;
}

void Ship::handleGravity(Map &mainMap) {
  if(!mainMap.checkCollision(entitySprite)) {
    gravityAcceleration += 0.135;
    gravityAcceleration > 20 ? gravityAcceleration = 20 : gravityAcceleration = gravityAcceleration;
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

sf::RectangleShape Ship::getRect() {
  return this->collisionBox;
}