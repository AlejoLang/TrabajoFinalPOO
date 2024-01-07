#ifndef ASTEROIDCOLLECTION_H
#define ASTEROIDCOLLECTION_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Obstacle.h"
#include "Asteroid.h"
#include "Airplane.h"
#include "Ship.h"
#include "Collision.h"

class ObstaclesCollection {
  private:
    std::vector<Obstacle *> obstaclesVector;
    std::vector<sf::Texture> asteroidTexures;
    std::vector<sf::Texture> airplaneTexures;
    sf::Clock generationClock; 
    float generationTime;
  public:
    ObstaclesCollection();
    void update(sf::View &mainView, Ship *playerShip, int gameDifficulty);
    void updateGenerationTime(int gameDifficulty);
    void handleObstaclesGeneration(sf::View &mainView, Ship *playerShip);
    void handleObstaclesCollision(Ship *playerShip);
    void handleObstaclesRemove(sf::View &mainView);
    void drawIn(sf::RenderWindow &window);
    ~ObstaclesCollection();
};

#endif