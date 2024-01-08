#ifndef FUELREFILLER_H
#define FUELREFILLER_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
class Ship;

class FuelRefiller : public Entity {
  protected:
    std::string type;
  public:
    FuelRefiller(sf::Texture &texture, std::string fuelType, sf::View &view);
    bool checkAndHandleCollision(Ship *player);
    ~FuelRefiller() {};
};

#endif