#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "DeathScene.h"
#include "MenuScene.h"
#include "Ship.h"
#include "Collision.h"
#include <random>
#include <vector>
#include <math.h>

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
  playerShip->update(game, mainMap);
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);
  mainObstaclesCollection.update(mainView, playerShip, game.getGameDifficulty());
  mainRefillerCollection.update(mainView, playerShip, game.getGameDifficulty());
  mainHud.update(playerShip, mainView);
  updateBackground(playerShip->getAltitudeKm());
  updateGameDifficulty(game, playerShip->getAltitudeKm());
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
  if(altitude < 10) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - 1080) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    }
  } else if( altitude < 20) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - (1080*2)) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y) - (1080*2)) {
      background.setTextureRect({0, background.getTextureRect().top - 3, background.getTextureRect().width, background.getTextureRect().height - 3});
    }
  } else if (altitude < 30) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y) - (1080*3)) {
      background.setTextureRect({0, background.getTextureRect().top + 3, background.getTextureRect().width, background.getTextureRect().height + 3});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y) - (1080*3)) {
      background.setTextureRect({0, background.getTextureRect().top - 3, background.getTextureRect().width, background.getTextureRect().height - 3});
    }
  } else if(altitude < 40){
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

void PlayScene::updateGameDifficulty(Game &game, float altitude) {
  if(altitude < 10) {
    game.setGameDifficulty(1);
  } else if( altitude < 20) {
    game.setGameDifficulty(2);
  } else if (altitude < 30) {
    game.setGameDifficulty(3);
  } else if(altitude < 40){
    game.setGameDifficulty(4);
  }
}

PlayScene::~PlayScene() {
  if (playerShip != nullptr) {
    delete playerShip;
    playerShip = nullptr;
  }
}