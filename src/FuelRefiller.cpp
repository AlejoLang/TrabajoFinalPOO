#include "FuelRefiller.h"
#include "Ship.h"
#include "Collision.h"
#include <string>

FuelRefiller::FuelRefiller(sf::Texture &texture, std::string fuelType, sf::View &view) : Entity(texture) {
  /* Set refiller type */
  this->type = fuelType;

  /* Set generation range inside the screen */
  int minX = int(view.getCenter().x - view.getSize().x / 2.0f);
  int maxX = int(view.getCenter().x + view.getSize().x / 2.0f);

  /* Place the refiller in a place between minX and maxX */
  entitySprite.setPosition(float(minX + rand()%(maxX - minX + 1)), view.getCenter().y - view.getSize().y / 2.0f - entitySprite.getGlobalBounds().height - 100.0f);
}

bool FuelRefiller::checkAndHandleCollision(Ship *player){
  /* Check for collision and increase player fuel depending on refiller type */
  /* Returns true if a collision is detected in order to remove the refiller in the collection, otherwise returns false */
  if(this->collides(player->getSprite())) {
    if(type == "LOX") {
      player->increaseLOX(100);
    } else if (type == "CH4") {
      player->increaseCH4(30);
    }
    return true;
  }
  return false;
}