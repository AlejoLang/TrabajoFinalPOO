#include "Game.h"
#include "Scene.h"
#include "DeathScene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include <vector>
#include <fstream>
#include <cstring>

DeathScene::DeathScene(Game &game, sf::RenderWindow &window, int points, sf::Font* gameFont) 
          : Scene(gameFont)
          , backToMenu("Menu", gameFont)
          , restartGame("Restart", gameFont)
{
  mainText.setString("YOU DIED");
  mainText.setFont(*sceneFont);
  mainText.setFillColor(sf::Color::Red);
  mainText.setCharacterSize(72);
  mainText.setOrigin(getCenter(mainText));
  mainText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f  - 200);
  pointsText.setString("Total points: " + std::to_string(points));
  pointsText.setFont(*sceneFont);
  pointsText.setCharacterSize(42);
  pointsText.setOrigin(getCenter(pointsText));
  pointsText.setPosition(getPlaceBelow(mainText, pointsText, 50));
  backToMenu.setPos(getPlaceBelow(pointsText, backToMenu.getBox(), 100));
  restartGame.setPos(getPlaceBelow(backToMenu.getBox(), restartGame.getBox(), 20));
  updateHighscores(game, points);
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  backToMenu.update(window);
  restartGame.update(window);
  if(backToMenu.isClicked(sceneEvent, window)){
    std::vector <HighscoreStruct> aux = game.gameHighscores.getHighscores();
    game.changeScene(new MenuScene(game, window, sceneFont));
  }
  if(restartGame.isClicked(sceneEvent, window)){
    game.changeScene(new PlayScene(game, window, sceneFont));
  }
  if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
    game.changeScene(new MenuScene(game, window, sceneFont));
  }
}

void DeathScene::processEvent(sf::Event &ev){
  sceneEvent = ev;
}

void DeathScene::updateHighscores(Game &game, int points) {
  if(game.username == "") {
    game.username = "Player";
  }
  HighscoreStruct newHs(game.username, points);
  game.gameHighscores.addScore(newHs);
}

void DeathScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(mainText);
  window.draw(pointsText);
  backToMenu.drawIn(window);
  restartGame.drawIn(window);
}


