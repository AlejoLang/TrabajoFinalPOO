#include "ObstaclesCollection.h"
#include "Obstacle.h"
#include "Asteroid.h"
#include "Airplane.h"
#include "Ship.h"
#include "Collision.h"
#include <vector>
#include <math.h>


ObstaclesCollection::ObstaclesCollection() 
                    : generationTime(0.8f) 
{
  /* Load asteroids textures */
  for (size_t i = 0; i < 2; i++) {
    sf::Texture aux;
    asteroidTexures.push_back(aux);
    if(!asteroidTexures[i].loadFromFile("./resources/textures/Asteroid"+ std::to_string(i + 1)+".png")) { exit(1); }
  }

  /* Load airplanes textures */
  for (size_t i = 0; i < 2; i++) {
    sf::Texture aux;
    airplaneTexures.push_back(aux);
    if(!airplaneTexures[i].loadFromFile("./resources/textures/Airplane"+ std::to_string(i + 1)+".png")) { exit(1); }
  }
}

void ObstaclesCollection::update(sf::View &mainView, Ship *playerShip, int gameDifficulty) {
  updateGenerationTime(gameDifficulty);
  handleObstaclesGeneration(mainView, playerShip);

  /* Update each obstacle */
  for (Obstacle *obs: obstaclesVector) {
    obs->update();
  }

  handleObstaclesCollision(playerShip);
  handleObstaclesRemove(mainView);
}

void ObstaclesCollection::updateGenerationTime(int gameDifficulty) {
  /* Change objects generation time based on game difficulty */
  switch (gameDifficulty) {
    case 1:
      generationTime = 0.8f;
      break;
    case 2:
      generationTime = 0.6f;
      break;
    case 3:
      generationTime = 0.4f;
      break;
    case 4:
      generationTime = 0.2f;
      break;
    default:
      break;
  }
}

void ObstaclesCollection::handleObstaclesGeneration(sf::View &mainView, Ship *playerShip) {
  if(generationClock.getElapsedTime().asSeconds() > generationTime) {
    /* set varaible for player altitude and a random number */
    float playerAltitude = playerShip->getAltitudeKm();
    float randomNumber = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    /* Generates airplanes, asteroids or a mix of both based on altitude and random number */
    if(playerAltitude > 0.1 && playerAltitude < 10) {  /* 100% airplanes */
      Obstacle *newAirplane = new Airplane(airplaneTexures, mainView);
      obstaclesVector.push_back(newAirplane);
    } else if(playerAltitude > 0.1 && playerAltitude < 20) {
      if(playerAltitude > 0.1 && randomNumber > 0.3) {  /* 70% airplanes, 30% asteroids */
        Obstacle *newAirplane = new Airplane(airplaneTexures, mainView); 
        obstaclesVector.push_back(newAirplane);
      } else {
        Obstacle *newAsteroid = new Asteroid(asteroidTexures, mainView);
        obstaclesVector.push_back(newAsteroid);
      }
    } else if(playerAltitude > 0.1 && playerAltitude < 30) {  /* 30% airplanes, 70% asteroids */
      if(randomNumber < 0.3) {
        Obstacle *newAirplane = new Airplane(airplaneTexures, mainView);
        obstaclesVector.push_back(newAirplane);
      } else {
        Obstacle *newAsteroid = new Asteroid(asteroidTexures, mainView);
        obstaclesVector.push_back(newAsteroid);
      }
    } else if(playerAltitude > 40) { /* 100% asteroids */
      Obstacle *newAsteroid = new Asteroid(asteroidTexures, mainView);
      obstaclesVector.push_back(newAsteroid);
    }
    generationClock.restart();
  }
}

void ObstaclesCollection::handleObstaclesCollision(Ship *playerShip) {
  /* Iterates through each obstacles searching for collisions */
  for (Obstacle *obs: obstaclesVector) {
    if(obs->collides(playerShip->getSprite())){
      playerShip->explode();
    }
  }
}

void ObstaclesCollection::handleObstaclesRemove(sf::View &mainView) {
  /* Remove obstacle that are above the view */
  for (size_t i = 0; i < obstaclesVector.size(); ++i) {
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
  /* Remove all remaining obstacles */
  for (Obstacle *obs: obstaclesVector) {
    delete obs;
  }
}