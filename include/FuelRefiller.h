#ifndef FUELREFILLER_H
#define FUELREFILLER_H
#include <SFML/Graphics.hpp>
#include <string>
#include "Entity.h"
#include "Collision.h"
#include "Ship.h"

class FuelRefiller : public Entity {
  protected:
    std::string type;
  public:
    FuelRefiller(sf::Texture &texture, std::string fuelType, sf::View &view);
    virtual void update(Ship *player);
};

#endif