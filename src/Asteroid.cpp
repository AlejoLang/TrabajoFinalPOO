#include "Asteroid.h"
#include <iostream>
#include <math.h>

Asteroid::Asteroid(sf::Texture &astText, sf::View &view) {
  int velocityMax = 5;
  int velocityMin = -5;
  this->setTexture(astText);
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  entitySprite.setOrigin(astText.getSize().x / 2.0f, astText.getSize().y / 2.0f);
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - astText.getSize().y);
  float scale = static_cast<int>(std::round(rand() % 4 + 1));
  entitySprite.setScale(scale, scale);
  asteroidCollisionBox.setRadius(entitySprite.getGlobalBounds().height / 2.0f - 10);
  asteroidCollisionBox.setOrigin(asteroidCollisionBox.getRadius(), asteroidCollisionBox.getRadius());
  asteroidVelocity = {velocityMin + rand()%(velocityMax - velocityMin + 1), velocityMin + rand()%(velocityMax - velocityMin + 1)};
}

void Asteroid::update() {
  entitySprite.move(asteroidVelocity);
  asteroidCollisionBox.setPosition(entitySprite.getPosition());
}

sf::CircleShape Asteroid::getCollisionBox() {
  return this->asteroidCollisionBox;
}

bool Asteroid::checkCollisionWithObject(sf::Sprite &sprite) {
  return asteroidCollisionBox.getGlobalBounds().intersects(sprite.getGlobalBounds());
}