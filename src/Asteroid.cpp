#include "Asteroid.h"

Asteroid::Asteroid(std::vector<sf::Texture> &asteroidTexures, sf::View &view) : Obstacle() {
  entitySprite.setTexture(asteroidTexures[static_cast<int>(std::round(rand() % 2))]);
  int velocityMax = 7;
  int velocityMin = -7;
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  float scale = static_cast<int>(std::round(rand() % 3 + 2));
  entitySprite.setScale(scale, scale);
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
  obstacleVelocity = {float(velocityMin + rand()%(velocityMax - velocityMin + 1)), float(abs(velocityMin + rand()%(velocityMax - velocityMin + 1)))};
}