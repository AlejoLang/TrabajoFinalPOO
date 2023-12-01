#include "DeathScene.h"
#include <iostream>

DeathScene::DeathScene() {
  if(!sceneFont.loadFromFile("./resources/fonts/Roboto-Regular.ttf")){exit(1);};
  mainText.setString("YOU DIED");
  mainText.setFont(sceneFont);
  mainText.setColor(sf::Color::White);
  mainText.setCharacterSize(48);
  button.setSize({100, 100});
  button.setOrigin(50, 50);
  button.setPosition({400, 400});
  backText.setString("Back");
  backText.setPosition(button.getPosition());
}

void DeathScene::update(Game &game, sf::RenderWindow &window) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)){
    game.changeScene(new MenuScene());
  }
}

void DeathScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(mainText);
}


