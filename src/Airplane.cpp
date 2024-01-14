#include "Airplane.h"
#include <math.h>

Airplane::Airplane(std::vector<sf::Texture> &planeTexures, sf::View &view) : Obstacle() {
  /* Set texture randomly between the two given */
  entitySprite.setTexture(planeTexures[static_cast<int>(std::round(rand() % planeTexures.size()))]);

  /* Set max and min velocity*/
  int velocityMax = 7;
  int velocityMin = -7;

  /* Set generation range inside the screen */
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;

  /* Set airplane position, and velocity (the velocity its only in the X anxis, the y velocity its 0) */
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
  obstacleVelocity = {float(velocityMin + rand()%(velocityMax - velocityMin + 1)), 0};

  /* Flips the entity sprite if its movith to the right */
  if(obstacleVelocity.x > 0) {
    entitySprite.setScale(-1, 1);
  }
}