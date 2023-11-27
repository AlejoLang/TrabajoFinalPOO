#ifndef ASTEROIDCOLLECTION_H
#define ASTEROIDCOLLECTION_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Asteroid.h"
#include "Ship.h"
#include "Collision.h"

class AsteroidCollection {
  private:
    std::vector<Asteroid *> asteroidsVector;
    std::vector<sf::Texture> asteroidTexures;
    sf::Clock asteroidGenerationClock; 
    float asteroidGenerationTime;
  public:
    AsteroidCollection();
    void update(sf::View &mainView, Ship *playerShip);
    void handleAsteroidGeneration(sf::View &mainView);
    void handleAsteroidCollision(Ship *playerShip);
    void handleAsteroidRemove(sf::View &mainView);
    void drawIn(sf::RenderWindow &window);
    ~AsteroidCollection();
};

#endif