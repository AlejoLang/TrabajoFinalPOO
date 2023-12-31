#include <SFML/Graphics.hpp>
#include "MenuScene.h"
#include <string>
#include <iostream>

MenuScene::MenuScene(sf::RenderWindow &window, sf::Font* gameFont)
          :Scene(gameFont)
          , goToPlayButton("Play", gameFont) 
          , exitButton("Exit", gameFont)
          , goToHighscoresButton("Highscores", gameFont)
{
  titleText.setFont(*sceneFont);
  subtitleText.setFont(*sceneFont);
  titleText.setString("T-24:00:00");
  subtitleText.setString("Presiona <Enter> para jugar");
  titleText.setCharacterSize(72);
  titleText.setOrigin(titleText.getGlobalBounds().width / 2.0f, titleText.getGlobalBounds().width / 2.0f);
  subtitleText.setOrigin(subtitleText.getGlobalBounds().width / 2.0f, subtitleText.getGlobalBounds().width / 2.0f);
  titleText.setFillColor(sf::Color::White);
  subtitleText.setFillColor(sf::Color::White);
  titleText.setPosition(960, 540);
  goToPlayButton.setPos({960, 640});
  goToHighscoresButton.setPos({960, 740});
  exitButton.setPos({960, 840});
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
  goToPlayButton.update(window);
  goToHighscoresButton.update(window);
  exitButton.update(window);
  if(goToPlayButton.isClicked(window)) {
    game.changeScene(new PlayScene(window, sceneFont));
  }
  if(exitButton.isClicked(window)) {
    window.close();
  }
  if(goToHighscoresButton.isClicked(window)) {
    game.changeScene(new HighscoresScene(window, game.gameHighscores, sceneFont));
  }
}

void MenuScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(titleText);
  window.draw(subtitleText);
  goToPlayButton.drawIn(window);
  exitButton.drawIn(window);
  goToHighscoresButton.drawIn(window);
}