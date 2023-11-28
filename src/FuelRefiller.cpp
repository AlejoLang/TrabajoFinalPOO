#include "FuelRefiller.h"
#include <iostream>

FuelRefiller::FuelRefiller(sf::Texture &texture, std::string fuelType, sf::View &view) : Entity(texture) {
  this->type = fuelType;
  int minX = view.getCenter().x - view.getSize().x / 2;
  int maxX = view.getCenter().x + view.getSize().x / 2;
  entitySprite.setPosition(minX + rand()%(maxX - minX + 1), view.getCenter().y - view.getSize().y / 2 - entitySprite.getGlobalBounds().height - 100);
}

bool FuelRefiller::checkAndHandleCollision(Ship *player){
  if(this->collides(player->getSprite())) {
    if(type == "LOX") {
      player->increaseLOX(100);
    } else if (type == "CH4") {
      player->increaseCH4(100);
    }
    return true;
  }
  return false;
}