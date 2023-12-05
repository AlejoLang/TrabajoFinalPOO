#include "DeathScene.h"
#include <iostream>

DeathScene::DeathScene(sf::RenderWindow &window, int points) 
          : backToMenu("Menu")
          , restartGame("Restart")
{
  if(!sceneFont.loadFromFile("./resources/fonts/RetroGaming.ttf")){exit(1);};
  mainText.setString("YOU DIED");
  mainText.setFont(sceneFont);
  mainText.setColor(sf::Color::Red);
  mainText.setCharacterSize(72);
  mainText.setOrigin(mainText.getGlobalBounds().width / 2.0f, mainText.getGlobalBounds().height / 2.0f);
  mainText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f  - 200);
  pointsText.setString("Total points: " + std::to_string(points));
  pointsText.setFont(sceneFont);
  pointsText.setCharacterSize(42);
  pointsText.setOrigin(pointsText.getGlobalBounds().width / 2.0f, pointsText.getGlobalBounds().height / 2.0f);
  pointsText.setPosition(mainText.getPosition().x, mainText.getPosition().y + mainText.getGlobalBounds().height + pointsText.getGlobalBounds().height);
  backToMenu.setPos({pointsText.getPosition().x, pointsText.getPosition().y + 100});
  restartGame.setPos({pointsText.getPosition().x, pointsText.getPosition().y + 180});
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  backToMenu.update(window);
  restartGame.update(window);
  if(backToMenu.isClicked(window)){
    game.changeScene(new MenuScene(window));
  }
  if(restartGame.isClicked(window)){
    game.changeScene(new PlayScene(window));
  }
}

void DeathScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(mainText);
  window.draw(pointsText);
  backToMenu.drawIn(window);
  restartGame.drawIn(window);
}


