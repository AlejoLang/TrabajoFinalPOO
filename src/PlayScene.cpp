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

PlayScene::PlayScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont) 
          :Scene(gameFont)
          , mainView(window.getDefaultView())
          , mainMap(window)
          , mainHud(gameFont)
          , mainRefillerCollection(game)
{ 
  /* Load textures */
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!backgroundTexture.loadFromFile("./resources/textures/background.png")){ exit(1); }

  /* Create player */
  playerShip = new Ship(game, playerTexture, mainMap);

  /* Set up background */
  background.setTexture(backgroundTexture);
  background.setTextureRect(sf::IntRect(0, backgroundTexture.getSize().y - 1080, backgroundTexture.getSize().x, backgroundTexture.getSize().y));
  background.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50);

  /* Initialize variables */
  deadFrameCount = 0;
  points = 0;
}

void PlayScene::update(Game &game, sf::RenderWindow &window) {
  /* Update player */
  playerShip->update(window, mainMap);

  /* Center view on player */
  mainView.setCenter(playerShip->getCenter().x, playerShip->getCenter().y - 350.f);

  /* Update obstavles and refillers collection*/
  mainObstaclesCollection.update(mainView, playerShip, game.getGameDifficulty());
  mainRefillerCollection.update(mainView, playerShip, game.getGameDifficulty());

  /* Update hud */
  mainHud.update(playerShip, mainView);

  updateBackground(playerShip->getAltitudeKm());
  updateGameDifficulty(game, playerShip->getAltitudeKm());
  updatePoints();

  /* Handle player dead */
  if(!playerShip->getStatus()){
    /* Wait until the explosion animation and the explosion sound stops playing and then change to the death scene */
    if(!playerShip->isExplosionSoundPlaying() && deadFrameCount > 12) {
      game.changeScene(new DeathScene(game, window, points, sceneFont));
    } else {
      deadFrameCount++;
    }
  }

  /* Check esc key press to go back to the menu */
  if (sceneEvent.key.code == sf::Keyboard::Escape) {
    game.changeScene(new MenuScene(game, window, sceneFont));
  }
}

void PlayScene::processEvent(sf::Event &ev) {
  sceneEvent = ev;
}

void PlayScene::updateBackground(float altitude) {
  int step = 3; /* Setp for the texture rect update, higher numbers are faster but less smooth*/
  /* Update the texture rect of the background based on altitude */
  if(altitude < 10) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y - (background.getTexture()->getSize().y / 4))) {
      background.setTextureRect({0, background.getTextureRect().top + step, background.getTextureRect().width, background.getTextureRect().height + step});
    }
  } else if( altitude < 20) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 2))) {
      background.setTextureRect({0, background.getTextureRect().top + step, background.getTextureRect().width, background.getTextureRect().height + step});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 2))) {
      background.setTextureRect({0, background.getTextureRect().top - step, background.getTextureRect().width, background.getTextureRect().height - step});
    }
  } else if (altitude < 30) {
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 3))) {
      background.setTextureRect({0, background.getTextureRect().top + step, background.getTextureRect().width, background.getTextureRect().height + step});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 2))) {
      background.setTextureRect({0, background.getTextureRect().top - step, background.getTextureRect().width, background.getTextureRect().height - step});
    }
  } else if(altitude < 40){
    if(background.getTextureRect().top < int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 4))) {
      background.setTextureRect({0, background.getTextureRect().top + step, background.getTextureRect().width, background.getTextureRect().height + step});
    } else if (background.getTextureRect().top > int(background.getTexture()->getSize().y - ((background.getTexture()->getSize().y / 4) * 2))) {
      background.setTextureRect({0, background.getTextureRect().top - step, background.getTextureRect().width, background.getTextureRect().height - step});
    }
  }
  background.setPosition(mainView.getCenter());
}

void PlayScene::updatePoints() {
  points = int((playerShip->getAltitudeKm() * 100) + ((playerShip->getCH4() + playerShip->getLOX()) * 0.5));
}

void PlayScene::updateGameDifficulty(Game &game, float altitude) {
  /* Set a number for the game difficulty based on altitude */
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

void PlayScene::drawIn(sf::RenderWindow& window) {
  window.setView(mainView);
  window.draw(background);
  playerShip->drawIn(window);
  mainObstaclesCollection.drawIn(window);
  mainRefillerCollection.drawIn(window);
  mainMap.drawIn(window);
  mainHud.draw(window);
}

PlayScene::~PlayScene() {
  /* Remove the player */
  if (playerShip != nullptr) {
    delete playerShip;
    playerShip = nullptr;
  }
}