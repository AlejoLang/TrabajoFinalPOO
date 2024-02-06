#include "Game.h"
#include "Scene.h"
#include "DeathScene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "GetGap.h"
#include <vector>
#include <fstream>
#include <cstring>

DeathScene::DeathScene(Game &game, sf::RenderWindow &window, int points, sf::Font* gameFont) 
          : Scene(gameFont)
          , backToMenu("Menu", gameFont)
          , restartGame("Restart", gameFont)
{
  /* Set title text */
  mainText.setString("YOU DIED");
  mainText.setFont(*sceneFont);
  mainText.setFillColor(sf::Color::Red);
  mainText.setCharacterSize(72);
  mainText.setOrigin(getCenter(mainText));
  mainText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f  - 200);

  /* Set subtitle text */
  pointsText.setString("Total points: " + std::to_string(points));
  pointsText.setFont(*sceneFont);
  pointsText.setCharacterSize(42);
  pointsText.setOrigin(getCenter(pointsText));
  pointsText.setPosition(getPlaceBelow(mainText, pointsText, 50));

  /* Set buttons position */
  backToMenu.setPos(getPlaceBelow(pointsText, backToMenu.getBox(), 100));
  restartGame.setPos(getPlaceBelow(backToMenu.getBox(), restartGame.getBox(), 20));

  updateHighscores(game, points);
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  /* Set buttons color on hover*/
  backToMenu.update(window);
  restartGame.update(window);

  /* Check for keyboard or mouse button press events */
  checkEvents(game, window);
}

void DeathScene::checkEvents(Game& game, sf::RenderWindow& window) {
  if (backToMenu.isClicked(sceneEvent, window)) {
    game.changeScene(new MenuScene(game, window, sceneFont));
  }
  if (restartGame.isClicked(sceneEvent, window)) {
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
  /* Put default username if the username is blank */
  if(game.getUsername() == "") {
    game.setUsername("Player");
  }
  
  HighscoreStruct newHs(game.getUsername(), points);
  game.getHighscores().addScore(newHs);
}

void DeathScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(mainText);
  window.draw(pointsText);
  backToMenu.drawIn(window);
  restartGame.drawIn(window);
}


