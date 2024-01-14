#include "Asteroid.h"
#include <math.h>

Asteroid::Asteroid(std::vector<sf::Texture> &asteroidTexures, sf::View &view) : Obstacle() {
  /* Set texture randomly between the two given */
  entitySprite.setTexture(asteroidTexures[static_cast<int>(std::round(rand() % 2))]);

  /* Set max and min velocity */
  int velocityMax = 7;
  int velocityMin = -7;

  /* Set generation range inside the screen */
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;

  /* Choose a random scale between 2 and 4*/
  float scale = static_cast<float>(rand() % 3 + 2);

  /* Set asteroid scale, position and velocity */
  entitySprite.setScale(scale, scale);
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
  obstacleVelocity = {float(velocityMin + rand()%(velocityMax - velocityMin + 1)), float(abs(velocityMin + rand()%(velocityMax - velocityMin + 1)))};
}