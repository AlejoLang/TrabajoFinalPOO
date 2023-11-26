#include "Asteroid.h"
#include <iostream>
#include <math.h>

Asteroid::Asteroid(sf::Texture &astText, sf::View &view) : Entity(astText) {
  int velocityMax = 5;
  int velocityMin = -5;
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - astText.getSize().y);
  float scale = static_cast<int>(std::round(rand() % 4 + 1));
  entitySprite.setScale(scale, scale);
  collisionBox.setSize({entitySprite.getGlobalBounds().width / 1.5f , entitySprite.getGlobalBounds().height / 1.5f});
  collisionBox.setOrigin(collisionBox.getSize() / 2.0f);
  asteroidVelocity = {velocityMin + rand()%(velocityMax - velocityMin + 1), velocityMin + rand()%(velocityMax - velocityMin + 1)};
}

void Asteroid::update() {
  entitySprite.move(asteroidVelocity);
  collisionBox.setPosition(entitySprite.getPosition());
}

bool Asteroid::checkCollisionWithObject(sf::RectangleShape &objectCollisionBox) {
  return collisionBox.getGlobalBounds().intersects(objectCollisionBox.getGlobalBounds());
}