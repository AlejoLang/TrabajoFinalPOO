#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "InstructionsScene.h"
#include "HighscoresScene.h"
#include "MenuScene.h"
#include "GetGap.h"
#include <string>

MenuScene::MenuScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont)
          :Scene(gameFont)
          , nameInput(*gameFont, 36, sf::Color::White)
          , goToPlayButton("Play", gameFont) 
          , exitButton("Exit", gameFont)
          , goToHighscoresButton("Highscores", gameFont)
          , volumeSelector("Volume", "above", gameFont)
{
  /* Set up title */
  titleText.setFont(*sceneFont);
  titleText.setString("T-24:00:00");
  titleText.setCharacterSize(72);
  titleText.setOrigin(getCenter(titleText));
  titleText.setFillColor(sf::Color::White);
  titleText.setPosition({window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 150.0f});

  /* Set up input field */
  nameInput.setMaxChars(20);
  nameInput.setValue(game.getUsername());
  nameInput.setString(game.getUsername());
  nameInput.setOrigin(getCenter(nameInput));
  nameInput.setPosition(getPlaceBelow(titleText, nameInput, 140));
  nameInput.setSingleWord(true);

  /* Place buttons */
  goToPlayButton.setPos(getPlaceBelow(nameInput, goToPlayButton.getBox(), 80.f));
  goToHighscoresButton.setPos(getPlaceBelow(goToPlayButton.getBox(), goToHighscoresButton.getBox(), 40.f));
  exitButton.setPos(getPlaceBelow(goToHighscoresButton.getBox(), exitButton.getBox(), 40.f));

  /* Configure volume selector */
  volumeSelector.setSize({200, 20});
  volumeSelector.setPos({window.getSize().x / 6.0f, window.getSize().y / 6.0f * 5.0f});
  volumeSelector.setValuePercentaje(game.getGameVolume());
  volumeSelector.setBorderColor(sf::Color::Red);
}

void MenuScene::update (Game &game, sf::RenderWindow &window) {
  /* Update countdown title */
  updateTitle();

  /* Update buttons color */
  goToPlayButton.update(window);
  goToHighscoresButton.update(window);
  exitButton.update(window);

  /* Update input field and username */
  nameInput.update();
  nameInput.setPosition({window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50});
  game.setUsername(nameInput.getValue());

  /* Update volume selector and game volume */
  volumeSelector.update(window);
  game.setGameVolume(volumeSelector.getValuePercentaje());

  /* Check for keyboard or mouse button press events */
  checkEvents(game, window);
}

void MenuScene::updateTitle() {
  sf::Time timeElapsed = timer.getElapsedTime();
  if (timeElapsed.asSeconds() >= 1.0) {
    countdownSeconds--;
    if (countdownSeconds < 0) {
      countdownSeconds = 59;
      countdownMinutes--;
    }
    if (countdownMinutes < 0) {
      countdownMinutes = 59;
      countdownHours--;
    }
    if (countdownHours < 0) {
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
}

void MenuScene::checkEvents(Game &game, sf::RenderWindow& window) {
  if (goToPlayButton.isClicked(sceneEvent, window)) {
    game.changeScene(new InstructionsScene(window, sceneFont));
    return;
  }
  if (goToHighscoresButton.isClicked(sceneEvent, window)) {
    game.changeScene(new HighscoresScene(game, window, sceneFont));
    return;
  }
  if (exitButton.isClicked(sceneEvent, window)) {
    window.close();
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
  window.draw(nameInput);
  goToPlayButton.drawIn(window);
  goToHighscoresButton.drawIn(window);
  exitButton.drawIn(window);
  volumeSelector.draw(window);
}