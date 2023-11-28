#include "FuelRefillerCollection.h"

fuelRefillerCollection::fuelRefillerCollection() : generationTime(5) {
  if(!LOXRefillerTexture.loadFromFile("./resources/textures/LOXRefiller.png")) { exit(1); }
  if(!CH4RefillerTexture.loadFromFile("./resources/textures/CH4Refiller.png")) { exit(1); }
}

void fuelRefillerCollection::update(sf::View &mainView, Ship *playerShip) {
  handleRefillerGeneration(mainView);
  handleRefillerCollision(playerShip);
  handleRefillerRemove(mainView);
}

void fuelRefillerCollection::handleRefillerGeneration(sf::View &mainView) {
  if(generationClock.getElapsedTime().asSeconds() > generationTime) {
    int type = rand() % 2;
    FuelRefiller *newRefiller;
    if(type == 0) {
      newRefiller = new FuelRefiller(LOXRefillerTexture, "LOX", mainView);
    } else if( type == 1) {
      newRefiller = new FuelRefiller(CH4RefillerTexture, "CH4", mainView);
    }
    fuelRefillersVector.push_back(newRefiller);
    generationClock.restart();
  }
}

void fuelRefillerCollection::handleRefillerCollision(Ship *playerShip) {
  for (size_t i = 0; i < fuelRefillersVector.size(); i++) {
    if(fuelRefillersVector[i]->checkAndHandleCollision(playerShip)){
      delete fuelRefillersVector[i];
      fuelRefillersVector.erase(fuelRefillersVector.begin() + i);
    }
  }
  
}

void fuelRefillerCollection::handleRefillerRemove(sf::View &mainView) {
  for (int i = 0; i < fuelRefillersVector.size(); ++i) {
    if(fuelRefillersVector[i]->getCenter().y - fuelRefillersVector[i]->getSprite().getGlobalBounds().height > mainView.getCenter().y + mainView.getSize().y / 2.0f){
      delete fuelRefillersVector[i];
      fuelRefillersVector.erase(fuelRefillersVector.begin() + i);
    }
  }
}

void fuelRefillerCollection::drawIn(sf::RenderWindow &window) {
  for (FuelRefiller *refiller: fuelRefillersVector) {
    refiller->drawIn(window);
  }
}

fuelRefillerCollection::~fuelRefillerCollection() {
  for (FuelRefiller *refiller: fuelRefillersVector) {
    delete refiller;
  }
}