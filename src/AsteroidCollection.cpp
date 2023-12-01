#include "AsteroidCollection.h"

AsteroidCollection::AsteroidCollection() : asteroidGenerationTime(0.4) {
  for (size_t i = 0; i < 2; i++) {
    sf::Texture aux;
    asteroidTexures.push_back(aux);
    if(!asteroidTexures[i].loadFromFile("./resources/textures/Asteroid"+ std::to_string(i + 1)+".png")) { exit(1); }
  }
}

void AsteroidCollection::update(sf::View &mainView, Ship *playerShip) {
  handleAsteroidGeneration(mainView);
  for (Asteroid *a: asteroidsVector) {
    a->update();
  }
  handleAsteroidCollision(playerShip);
  handleAsteroidRemove(mainView);
}

void AsteroidCollection::handleAsteroidGeneration(sf::View &mainView) {
  if(asteroidGenerationClock.getElapsedTime().asSeconds() > asteroidGenerationTime) {
    Asteroid *newAsteroid = new Asteroid(asteroidTexures[static_cast<int>(std::round(rand() % 2))], mainView);
    asteroidsVector.push_back(newAsteroid);
    asteroidGenerationClock.restart();
  }
}

void AsteroidCollection::handleAsteroidCollision(Ship *playerShip) {
  for (Asteroid *a: asteroidsVector) {
    if(a->collides(playerShip->getSprite())){
      playerShip->explode();
    }
  }
}

void AsteroidCollection::handleAsteroidRemove(sf::View &mainView) {
  for (int i = 0; i < asteroidsVector.size(); ++i) {
    if(asteroidsVector[i]->getCenter().y - asteroidsVector[i]->getSprite().getGlobalBounds().height > mainView.getCenter().y + mainView.getSize().y / 2.0f){
      delete asteroidsVector[i];
      asteroidsVector.erase(asteroidsVector.begin() + i);
    }
  }
}

void AsteroidCollection::drawIn(sf::RenderWindow &window) {
  for (Asteroid *a: asteroidsVector) {
    a->drawIn(window);
  }
}

AsteroidCollection::~AsteroidCollection(){
  for (Asteroid *a: asteroidsVector) {
    delete a;
  }
}