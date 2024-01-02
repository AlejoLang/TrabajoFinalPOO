#include "DeathScene.h"
#include <vector>
#include <iostream>

DeathScene::DeathScene(Game &game, sf::RenderWindow &window, int points, sf::Font* gameFont) 
          : Scene(gameFont)
          , backToMenu("Menu", gameFont)
          , restartGame("Restart", gameFont)
{
  mainText.setString("YOU DIED");
  mainText.setFont(*sceneFont);
  mainText.setColor(sf::Color::Red);
  mainText.setCharacterSize(72);
  mainText.setOrigin(mainText.getGlobalBounds().width / 2.0f, mainText.getGlobalBounds().height / 2.0f);
  mainText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f  - 200);
  pointsText.setString("Total points: " + std::to_string(points));
  pointsText.setFont(*sceneFont);
  pointsText.setCharacterSize(42);
  pointsText.setOrigin(pointsText.getGlobalBounds().width / 2.0f, pointsText.getGlobalBounds().height / 2.0f);
  pointsText.setPosition(mainText.getPosition().x, mainText.getPosition().y + mainText.getGlobalBounds().height + pointsText.getGlobalBounds().height);
  backToMenu.setPos({pointsText.getPosition().x, pointsText.getPosition().y + 100});
  restartGame.setPos({pointsText.getPosition().x, pointsText.getPosition().y + 180});
  updateHighscores(game, points);
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  backToMenu.update(window);
  restartGame.update(window);
  if(backToMenu.isClicked(window)){
    std::vector <HighscoreStruct> aux = game.gameHighscores.getHighscores();
    game.changeScene(new MenuScene(window, sceneFont));
  }
  if(restartGame.isClicked(window)){
    game.changeScene(new PlayScene(window, sceneFont));
  }
  if (sceneEvent.key.code == sf::Keyboard::Escape) {
    game.changeScene(new MenuScene(window, sceneFont));
  }
}

void DeathScene::processEvent(sf::Event &ev){
  sceneEvent = ev;
}

void DeathScene::updateHighscores(Game &game, int points) {
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


