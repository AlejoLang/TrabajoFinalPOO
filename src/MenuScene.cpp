#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "InstructionsScene.h"
#include "HighscoresScene.h"
#include "MenuScene.h"
#include <string>

MenuScene::MenuScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont)
          :Scene(gameFont)
          , nameInput(*gameFont, 36, sf::Color::White)
          , goToPlayButton("Play", gameFont) 
          , exitButton("Exit", gameFont)
          , goToHighscoresButton("Highscores", gameFont)
          , volumeSelector("Volume", gameFont)
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
  titleText.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50});
  nameInput.setMaxChars(20);
  nameInput.setOrigin({nameInput.getGlobalBounds().getSize().x / 2.0f, nameInput.getGlobalBounds().getSize().y / 2.0f});
  nameInput.setValue(game.username);
  nameInput.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50});
  nameInput.setSingleWord(true);
  goToPlayButton.setPos(getPlaceBelow(nameInput, goToPlayButton.getBox(), 40.f));
  goToHighscoresButton.setPos(getPlaceBelow(goToPlayButton.getBox(), goToHighscoresButton.getBox(), 20.f));
  exitButton.setPos(getPlaceBelow(goToHighscoresButton.getBox(), exitButton.getBox(), 20.f));
  volumeSelector.setSize({200, 20});
  volumeSelector.setPos({window.getSize().x / 6.0f, window.getSize().y / 6.0f * 5.0f});
  volumeSelector.setValuePercentaje(game.getGameVolume());
  volumeSelector.setBorderColor(sf::Color::Red);
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
  nameInput.update();
  nameInput.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50});
  game.username = nameInput.getValue();
  volumeSelector.update(window);
  game.setGameVolume(volumeSelector.getValuePercentaje());
  if(goToPlayButton.isClicked(window) && game.isFocused) {
    game.changeScene(new InstructionsScene(window, sceneFont));
  }
  if(exitButton.isClicked(window) && game.isFocused) {
    window.close();
  }
  if(goToHighscoresButton.isClicked(window) && game.isFocused) {
    game.changeScene(new HighscoresScene(window, game.gameHighscores, sceneFont));
  }
  if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
    window.close();
  }
}

void MenuScene::processEvent(sf::Event &ev){
  nameInput.processEvent(ev);
  sceneEvent = ev;
}

void MenuScene::drawIn(sf::RenderWindow &window) {
  window.setView(window.getDefaultView());
  window.draw(titleText);
  window.draw(subtitleText);
  goToPlayButton.drawIn(window);
  exitButton.drawIn(window);
  goToHighscoresButton.drawIn(window);
  volumeSelector.draw(window);
  window.draw(nameInput);
}