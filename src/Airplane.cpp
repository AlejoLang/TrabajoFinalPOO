#include "Airplane.h"

Airplane::Airplane(std::vector<sf::Texture> &planeTexures, sf::View &view) : Obstacle() {
  entitySprite.setTexture(planeTexures[static_cast<int>(std::round(rand() % planeTexures.size()))]);
  int velocityMax = 7;
  int velocityMin = -7;
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
  obstacleVelocity = {velocityMin + rand()%(velocityMax - velocityMin + 1), 0};
}