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
}

void PlayScene::update() {
  playerShip->update(mainMap);
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainAsteroidCollection.update(mainView, playerShip);
  mainRefillerCollection.update(mainView, playerShip);
  mainHud.update(playerShip, mainView);
  background.setPosition(mainView.getCenter());
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


PlayScene::~PlayScene() {
  delete playerShip;
  
}