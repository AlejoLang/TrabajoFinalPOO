#include "FuelRefillerCollection.h"

FuelRefillerCollection::FuelRefillerCollection() : generationTime(5) {
  if(!LOXRefillerTexture.loadFromFile("./resources/textures/LOXRefiller.png")) { exit(1); }
  if(!CH4RefillerTexture.loadFromFile("./resources/textures/CH4Refiller.png")) { exit(1); }
}

void FuelRefillerCollection::update(sf::View &mainView, Ship *playerShip, int gameDifficulty) {
  updateGenerationTime(gameDifficulty);
  handleRefillerGeneration(mainView, playerShip);
  handleRefillerCollision(playerShip);
  handleRefillerRemove(mainView);
}

void FuelRefillerCollection::updateGenerationTime(int gameDifficulty) {
  switch (gameDifficulty){
    case 1:
      generationTime = 4;
      break;
    case 2:
      generationTime = 8;
      break;
    case 3:
      generationTime = 12;
      break;
    case 4:
      generationTime = 16;
      break;
    default:
      break;
  }
}

void FuelRefillerCollection::handleRefillerGeneration(sf::View &mainView, Ship *playerShip) {
  if(playerShip->getAltitudeKm() < 0.5) { generationClock.restart(); }
  if(generationClock.getElapsedTime().asSeconds() > generationTime){
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

void FuelRefillerCollection::handleRefillerCollision(Ship *playerShip) {
  for (size_t i = 0; i < fuelRefillersVector.size(); i++) {
    if(fuelRefillersVector[i]->checkAndHandleCollision(playerShip)){
      delete fuelRefillersVector[i];
      fuelRefillersVector.erase(fuelRefillersVector.begin() + i);
    }
  }
  
}

void FuelRefillerCollection::handleRefillerRemove(sf::View &mainView) {
  for (size_t i = 0; i < fuelRefillersVector.size(); ++i) {
    if(fuelRefillersVector[i]->getCenter().y - fuelRefillersVector[i]->getSprite().getGlobalBounds().height > mainView.getCenter().y + mainView.getSize().y / 2.0f){
      delete fuelRefillersVector[i];
      fuelRefillersVector.erase(fuelRefillersVector.begin() + i);
    }
  }
}

void FuelRefillerCollection::drawIn(sf::RenderWindow &window) {
  for (FuelRefiller *refiller: fuelRefillersVector) {
    refiller->drawIn(window);
  }
}

FuelRefillerCollection::~FuelRefillerCollection() {
  for (FuelRefiller *refiller: fuelRefillersVector) {
    delete refiller;
  }
}