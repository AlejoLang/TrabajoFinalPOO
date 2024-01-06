#include <SFML/Graphics.hpp>
#include "PlayScene.h"
#include <random>
#include "Collision.h"
#include <iostream>

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font* gameFont) 
          :Scene(gameFont)
          , mainView(window.getDefaultView())
          , mainMap(window)
          , mainHud(gameFont)
{ 
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!backgroundTexture.loadFromFile("./resources/textures/background.png")){ exit(1); }
  playerShip = new Ship(playerTexture, mainMap);
  background.setTexture(backgroundTexture);
  background.setTextureRect(sf::IntRect(0, backgroundTexture.getSize().y - 1080, backgroundTexture.getSize().x, backgroundTexture.getSize().y));
  background.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50);
  deadFrameCount = 0;
}

void PlayScene::update(Game &game, sf::RenderWindow &window) {
  playerShip->update(mainMap);
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainObstaclesCollection.update(mainView, playerShip);
  mainRefillerCollection.update(mainView, playerShip);
  mainHud.update(playerShip, mainView);
  updateBackground(playerShip->getAltitudeKm());
  updatePoints();
  if(!playerShip->getStatus()){
    if(!playerShip->isExplosionSoundPlaying() && deadFrameCount > 12) {
      game.changeScene(new DeathScene(game, window, points, sceneFont));
    } else {
      deadFrameCount++;
    }
  } else if (sceneEvent.key.code == sf::Keyboard::Escape) {
    game.changeScene(new MenuScene(game, sceneFont));
  }
}

void PlayScene::processEvent(sf::Event &ev) {
  sceneEvent = ev;
}

void PlayScene::updateBackground(float altitude) {
  if(altitude < 5) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - 1080) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    }
  } else if( altitude < 10) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - (1080*2)) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y) - (1080*2)) {
      background.setTextureRect({0, background.getTextureRect().top - 3, background.getTextureRect().width, background.getTextureRect().height - 3});
    }
  } else if (altitude < 15) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - (1080*3)) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y) - (1080*3)) {
      background.setTextureRect({0, background.getTextureRect().top - 3, background.getTextureRect().width, background.getTextureRect().height - 3});
    }
  } else if(altitude < 20){
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - (1080*4)) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y) - (1080*4)) {
      background.setTextureRect({0, background.getTextureRect().top - 3, background.getTextureRect().width, background.getTextureRect().height - 3});
    }
  }
  background.setPosition(mainView.getCenter());
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  window.draw(background);
  playerShip->drawIn(window);
  mainObstaclesCollection.drawIn(window);
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