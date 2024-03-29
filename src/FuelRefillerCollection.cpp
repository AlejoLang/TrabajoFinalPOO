#include "Game.h"
#include "FuelRefillerCollection.h"
#include "FuelRefiller.h"
#include "Ship.h"
#include <vector>

FuelRefillerCollection::FuelRefillerCollection(Game &game) : generationTime(5) {
  /* Load refillers textures */
  if(!LOXRefillerTexture.loadFromFile("./resources/textures/LOXRefiller.png")) { exit(1); }
  if(!CH4RefillerTexture.loadFromFile("./resources/textures/CH4Refiller.png")) { exit(1); }

  /* Load collection sound */
  if(!collectionSoundFile.loadFromFile("./resources/sounds/collect.wav")) { exit(1); }

  /* Set collection sound */
  collectionSound.setBuffer(collectionSoundFile);
  collectionSound.setVolume(game.getGameVolume());
}

void FuelRefillerCollection::update(sf::View &mainView, Ship *playerShip, int gameDifficulty) {
  updateGenerationTime(gameDifficulty);
  handleRefillerGeneration(mainView, playerShip);
  handleRefillerCollision(playerShip);
  handleRefillerRemove(mainView);
}

void FuelRefillerCollection::updateGenerationTime(int gameDifficulty) {
  /* Increase the generation time based on altitude */
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
  /* Generates a random refiller type when the generation time matches the generation clock elapsed time */
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
  /* Remove the refiller and plays the collection sound don player collision */
  for (size_t i = 0; i < fuelRefillersVector.size(); i++) {
    if(fuelRefillersVector[i]->checkAndHandleCollision(playerShip)){
      collectionSound.play();
      delete fuelRefillersVector[i];
      fuelRefillersVector.erase(fuelRefillersVector.begin() + i);
    }
  }
}

void FuelRefillerCollection::handleRefillerRemove(sf::View &mainView) {
  /* Remove the refillers that are out of the screen */
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
  /* Delete the remaining refillers */
  for (FuelRefiller *refiller: fuelRefillersVector) {
    delete refiller;
  }
}