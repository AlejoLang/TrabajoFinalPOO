#ifndef FUELREFILLERCOLLECTION
#define FUELREFILLERCOLLECTION
#include <SFML/Graphics.hpp>
#include <vector>
#include "FuelRefiller.h"

class fuelRefillerCollection
{
  private:
    std::vector<FuelRefiller *> fuelRefillersVector;
    sf::Texture LOXRefillerTexture;
    sf::Texture CH4RefillerTexture;
    sf::Clock generationClock; 
    float generationTime;
  public:
    fuelRefillerCollection(/* args */);
    void update(sf::View &mainView, Ship *playerShip);
    void handleRefillerGeneration(sf::View &mainView);
    void handleRefillerCollision(Ship *playerShip);
    void handleRefillerRemove(sf::View &mainView);
    void drawIn(sf::RenderWindow &window);
    ~fuelRefillerCollection();
};


#endif