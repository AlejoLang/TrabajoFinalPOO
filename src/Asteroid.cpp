#include "Asteroid.h"
#include <iostream>
#include <math.h>

Asteroid::Asteroid(sf::Texture &astText, sf::View &view) : Entity(astText) {
  int velocityMax = 7;
  int velocityMin = -7;
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  float scale = static_cast<int>(std::round(rand() % 3 + 2));
  entitySprite.setScale(scale, scale);
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
  asteroidVelocity = {velocityMin + rand()%(velocityMax - velocityMin + 1), abs(velocityMin + rand()%(velocityMax - velocityMin + 1))};
}

void Asteroid::update() {
  entitySprite.move(asteroidVelocity);
}