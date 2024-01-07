#ifndef FUELREFILLERCOLLECTION
#define FUELREFILLERCOLLECTION
#include <SFML/Graphics.hpp>
#include <vector>
#include "FuelRefiller.h"
#include "Ship.h"

class FuelRefillerCollection
{
  private:
    std::vector<FuelRefiller *> fuelRefillersVector;
    sf::Texture LOXRefillerTexture;
    sf::Texture CH4RefillerTexture;
    sf::Clock generationClock; 
    float generationTime;
  public:
    FuelRefillerCollection(/* args */);
    void update(sf::View &mainView, Ship *playerShip, int gameDifficulty);
    void updateGenerationTime(int gameDifficulty);
    void handleRefillerGeneration(sf::View &mainView, Ship *playerShip);
    void handleRefillerCollision(Ship *playerShip);
    void handleRefillerRemove(sf::View &mainView);
    void drawIn(sf::RenderWindow &window);
    ~FuelRefillerCollection();
};


#endif