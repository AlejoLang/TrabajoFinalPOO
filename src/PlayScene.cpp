#include <SFML/Graphics.hpp>
#include "PlayScene.h"
#include <random>
#include "Collision.h"
#include <iostream>

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font* gameFont) 
          :Scene(gameFont)
          , mainMap(window)
          , mainView(window.getDefaultView())
          , mainHud(gameFont)
{ 
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!lowAltitudeBackgroundTexture.loadFromFile("./resources/textures/lowAltitudeSky.png")) { exit(1); }
  if(!midAltitudeBackgroundTexture.loadFromFile("./resources/textures/midAltitudeSky.png")) { exit(1); }
  if(!highAltitudeBackgroundTexture.loadFromFile("./resources/textures/highAltitudeSky.png")) { exit(1); }
  if(!spaceBackgroundTexture.loadFromFile("./resources/textures/spaceSky.png")) { exit(1); }
  playerShip = new Ship(playerTexture, mainMap, window);
  background.setTexture(lowAltitudeBackgroundTexture);
  background.setOrigin(lowAltitudeBackgroundTexture.getSize().x / 2.0f, lowAltitudeBackgroundTexture.getSize().y / 2.0f);
  deadFrameCount = 0;
}

void PlayScene::update(Game &game, sf::RenderWindow &window) {
  playerShip->update(mainMap);
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainAsteroidCollection.update(mainView, playerShip);
  mainRefillerCollection.update(mainView, playerShip);
  mainHud.update(playerShip, mainView);
  updateBackground(window, playerShip->getAltitudeKm());
  updatePoints();
  if(!playerShip->getStatus()){
    if(deadFrameCount > 12) {
      game.changeScene(new DeathScene(game, window, points, sceneFont));
    } else {
      deadFrameCount++;
    }
  } else if (sceneEvent.key.code == sf::Keyboard::Escape) {
    game.changeScene(new MenuScene(window, sceneFont));
  }
}

void PlayScene::processEvent(sf::Event &ev) {
  sceneEvent = ev;
}

void PlayScene::updateBackground(sf::RenderWindow &window, float altitude) {
  if(altitude < 0.5) {
    background.setTexture(lowAltitudeBackgroundTexture);
  } else if( altitude < 2) {
    background.setTexture(midAltitudeBackgroundTexture);
  } else if (altitude < 3) {
    background.setTexture(highAltitudeBackgroundTexture);
  } else if(altitude < 4){
    background.setTexture(spaceBackgroundTexture);
  }
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

void PlayScene::updatePoints() {
  points = (playerShip->getAltitudeKm() * 100) + ((playerShip->getCH4() + playerShip->getLOX()) * 0.5);
}

PlayScene::~PlayScene() {
  if (playerShip != nullptr) {
    delete playerShip;
    playerShip = nullptr;
  }
}