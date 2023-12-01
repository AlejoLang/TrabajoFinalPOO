#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include <string>

MenuScene::MenuScene() {
  menuFont.loadFromFile("./resources/fonts/RetroGaming.ttf");
  titleText.setFont(menuFont);
  subtitleText.setFont(menuFont);
  titleText.setString("T-24:00:00");
  subtitleText.setString("Presiona <Enter> para jugar");
  titleText.setCharacterSize(72);
  titleText.setOrigin(titleText.getGlobalBounds().width / 2.0f, titleText.getGlobalBounds().width / 2.0f);
  subtitleText.setOrigin(subtitleText.getGlobalBounds().width / 2.0f, subtitleText.getGlobalBounds().width / 2.0f);
  titleText.setFillColor(sf::Color::White);
  subtitleText.setFillColor(sf::Color::White);
  titleText.setPosition(960, 540);
  subtitleText.setPosition(960, 740);
}

void MenuScene::update (Game &game, sf::RenderWindow &window) {
  sf::Time timeElapsed = timer.getElapsedTime();
  if(timeElapsed.asSeconds() >= 1.0) {
    countdownSeconds--;
    if(countdownSeconds < 0) {
      countdownSeconds = 59;
      countdownMinutes--;
    }
    if(countdownMinutes < 0) {
      countdownMinutes = 59;
      countdownHours--;
    } 
    if(countdownHours < 0) {
      countdownHours = 24;
      countdownMinutes = 0;
      countdownSeconds = 0;
    }
    std::string title = "T-" + (countdownHours >= 10 ? std::to_string(countdownHours) : "0" + std::to_string(countdownHours)) + ":"
                          + (countdownMinutes >= 10 ? std::to_string(countdownMinutes) : "0" + std::to_string(countdownMinutes)) + ":"
                          + (countdownSeconds >= 10 ? std::to_string(countdownSeconds) : "0" + std::to_string(countdownSeconds));
    titleText.setString(title);
    timer.restart();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)){
    game.changeScene(new PlayScene(window, menuFont));
  }
}

void MenuScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(titleText);
  window.draw(subtitleText);
}