#include "ObstaclesCollection.h"

ObstaclesCollection::ObstaclesCollection() : generationTime(0.4) {
  for (size_t i = 0; i < 2; i++) {
    sf::Texture aux;
    asteroidTexures.push_back(aux);
    if(!asteroidTexures[i].loadFromFile("./resources/textures/Asteroid"+ std::to_string(i + 1)+".png")) { exit(1); }
  }
  for (size_t i = 0; i < 1; i++) {
    sf::Texture aux;
    airplaneTexures.push_back(aux);
    if(!airplaneTexures[i].loadFromFile("./resources/textures/Airplane"+ std::to_string(i + 1)+".png")) { exit(1); }
  }
}

void ObstaclesCollection::update(sf::View &mainView, Ship *playerShip) {
  handleObstaclesGeneration(mainView, playerShip);
  for (Obstacle *obs: obstaclesVector) {
    obs->update();
  }
  handleObstaclesCollision(playerShip);
  handleObstaclesRemove(mainView);
}

void ObstaclesCollection::handleObstaclesGeneration(sf::View &mainView, Ship *playerShip) {
  if(generationClock.getElapsedTime().asSeconds() > generationTime) {
    float playerAltitude = playerShip->getAltitudeKm();
    if(playerAltitude > 0.1 && playerAltitude < 10) {
      Obstacle *newAirplane = new Airplane(airplaneTexures, mainView);
      obstaclesVector.push_back(newAirplane);
    } else if(playerAltitude > 10) {
      Obstacle *newAsteroid = new Asteroid(asteroidTexures, mainView);
      obstaclesVector.push_back(newAsteroid);
    }
    generationClock.restart();
  }
}

void ObstaclesCollection::handleObstaclesCollision(Ship *playerShip) {
  for (Obstacle *obs: obstaclesVector) {
    if(obs->collides(playerShip->getSprite())){
      playerShip->explode();
    }
  }
}

void ObstaclesCollection::handleObstaclesRemove(sf::View &mainView) {
  for (int i = 0; i < obstaclesVector.size(); ++i) {
    if(obstaclesVector[i]->getCenter().y - obstaclesVector[i]->getSprite().getGlobalBounds().height > mainView.getCenter().y + mainView.getSize().y / 2.0f){
      delete obstaclesVector[i];
      obstaclesVector.erase(obstaclesVector.begin() + i);
    }
  }
}

void ObstaclesCollection::drawIn(sf::RenderWindow &window) {
  for (Obstacle *obs: obstaclesVector) {
    obs->drawIn(window);
  }
}

ObstaclesCollection::~ObstaclesCollection(){
  for (Obstacle *obs: obstaclesVector) {
    delete obs;
  }
}