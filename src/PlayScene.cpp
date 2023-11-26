#include <SFML/Graphics.hpp>
#include "PlayScene.h"
#include <random>

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font &gameFont) 
          : mainMap(window)
          , mainView(window.getDefaultView())
          , mainHud(gameFont)
          , asteroidGenerationTime(0.3)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!backgroundTexture.loadFromFile("./resources/textures/Background.png")) { exit(1); }
  for (size_t i = 0; i < 2; i++) {
    sf::Texture aux;
    asteroidTexures.push_back(aux);
    if(!asteroidTexures[i].loadFromFile("./resources/textures/Asteroid"+ std::to_string(i + 1)+".png")) { exit(1); }
  }
  playerShip = new Ship(playerTexture, window);
  background.setTexture(backgroundTexture);
  background.setOrigin(backgroundTexture.getSize().x / 2.0f, backgroundTexture.getSize().y / 2.0f);
}

void PlayScene::update() {
  playerShip->update(mainMap);
  handleAsteroidsGeneration();
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainHud.update(playerShip, mainView);
  background.setPosition(mainView.getCenter());
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  window.draw(background);
  playerShip->drawIn(window);
  window.draw(playerShip->getRect());
  handleAsteroidsDraw(window);
  mainMap.drawIn(window);
  mainHud.draw(window);
}

void PlayScene::handleAsteroidsGeneration() {
  /*if(asteroidGenerationClock.getElapsedTime().asSeconds() > asteroidGenerationTime) {
    Asteroid *newAsteroid = new Asteroid(asteroidTexures[static_cast<int>(std::round(rand() % 2))], mainView);
    asteroidsVector.push_back(newAsteroid);
    asteroidGenerationClock.restart();
  }
  for (Asteroid *a: asteroidsVector)
  {
    sf::RectangleShape shipSpt = playerShip->getRect();
    a->update();
    if(a->checkCollisionWithObject(shipSpt)){
      exit(1);
    }
  }*/
  
}

void PlayScene::handleAsteroidsDraw(sf::RenderWindow &window) {
  for(Asteroid *a: asteroidsVector) {
    a->drawIn(window);
    window.draw(a->getCollisionBox());
  }
}

PlayScene::~PlayScene() {
  delete playerShip;
  for (Asteroid *a: asteroidsVector){
    delete a;
  }
}