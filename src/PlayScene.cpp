#include <SFML/Graphics.hpp>
#include "PlayScene.h"
#include <random>
#include "Collision.h"

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font &gameFont) 
          : mainMap(window)
          , mainView(window.getDefaultView())
          , mainHud(gameFont)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!backgroundTexture.loadFromFile("./resources/textures/Background.png")) { exit(1); }
  playerShip = new Ship(playerTexture, mainMap, window);
  background.setTexture(backgroundTexture);
  background.setOrigin(backgroundTexture.getSize().x / 2.0f, backgroundTexture.getSize().y / 2.0f);
  deadFrameCount = 0;
}

void PlayScene::update(Game &game, sf::RenderWindow &window) {
  playerShip->update(mainMap);
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainAsteroidCollection.update(mainView, playerShip);
  mainRefillerCollection.update(mainView, playerShip);
  mainHud.update(playerShip, mainView);
  background.setPosition(mainView.getCenter());
  updatePoints();
  if(!playerShip->getStatus()){
    if(deadFrameCount > 12) {
      game.changeScene(new DeathScene(window, points));
    } else {
      deadFrameCount++;
    }
  }
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  window.draw(background);
  playerShip->drawIn(window);
  mainAsteroidCollection.drawIn(window);
  mainRefillerCollection.drawIn(window);
  mainMap.drawIn(window);
  mainHud.draw(window);
}

void PlayScene::updatePoints() {
  points = (playerShip->getAltitudeKm() * 100) + ((playerShip->getCH4() + playerShip->getLOX()) * 0.5);
}

PlayScene::~PlayScene() {
  delete playerShip;
  
}