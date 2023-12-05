#include "DeathScene.h"
#include <iostream>

DeathScene::DeathScene(sf::RenderWindow &window, int points) {
  if(!sceneFont.loadFromFile("./resources/fonts/RetroGaming.ttf")){exit(1);};
  mainText.setString("YOU DIED");
  mainText.setFont(sceneFont);
  mainText.setColor(sf::Color::Red);
  mainText.setCharacterSize(72);
  mainText.setOrigin(mainText.getGlobalBounds().width / 2.0f, mainText.getGlobalBounds().height / 2.0f);
  mainText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
  pointsText.setString("Total points: " + std::to_string(points));
  pointsText.setFont(sceneFont);
  pointsText.setCharacterSize(42);
  pointsText.setOrigin(pointsText.getGlobalBounds().width / 2.0f, pointsText.getGlobalBounds().height / 2.0f);
  pointsText.setPosition(mainText.getPosition().x, mainText.getPosition().y + mainText.getGlobalBounds().height + pointsText.getGlobalBounds().height);
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
    game.changeScene(new MenuScene(window));
  }
}

void DeathScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(mainText);
  window.draw(pointsText);
}


