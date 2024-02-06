#include "Game.h"
#include "Scene.h"
#include "HighscoresScene.h"
#include "MenuScene.h"
#include "GetGap.h"
#include <vector>
#include <string>
#include <iomanip>

HighscoresScene::HighscoresScene(Game& game, sf::RenderWindow &window, sf::Font* gameFont)
                :Scene(gameFont)
                , goToMenuButton("Menu", gameFont)
                , cleanHighscoresButton("Clean Highscores", gameFont, "auto")
{
  /* Title set up*/
  titleText.setFont(*sceneFont);
  titleText.setString("Highscores");
  titleText.setCharacterSize(72);
  titleText.setOrigin(GetGap::getCenter(titleText));
  titleText.setPosition({window.getSize().x / 2.0f, 100.0f});

  setUpHighscoresText(game, window);

  /* Set button positions */
  goToMenuButton.setPos({window.getSize().x / 2.0f, window.getSize().y - 100.0f});
  cleanHighscoresButton.setPos(GetGap::getPlaceRight(goToMenuButton.getBox(), cleanHighscoresButton.getBox(), 300));
}

void HighscoresScene::setUpHighscoresText(Game& game, sf::RenderWindow &window) {
  /* Load highscores vector */
  std::vector <HighscoreStruct> hsVector = game.getHighscores().getHighscoresVector();

  /* Make aux text */
  sf::Text auxName;
  sf::Text auxPoints;
  auxName.setFont(*sceneFont);
  auxPoints.setFont(*sceneFont);
  auxName.setCharacterSize(32);
  auxPoints.setCharacterSize(32);

  /* Iterate trough the higscores Vector */
  for (size_t i = 0; i < hsVector.size(); i++) {
    /* Copy a username and its points to the aux texts*/
    auxName.setString((std::string)hsVector[i].username);
    auxPoints.setString(std::to_string(hsVector[i].points));

    /* Add the aux texts to the texts vector*/
    highscoresTextsVector.push_back({auxName, auxPoints});

    /* Set origin of the texts pushed */
    highscoresTextsVector[i].first.setOrigin(0, highscoresTextsVector[i].first.getGlobalBounds().height / 2.0f);
    highscoresTextsVector[i].second.setOrigin(0, highscoresTextsVector[i].second.getGlobalBounds().height / 2.0f);

    /* Set position of the texts pushed*/
    highscoresTextsVector[i].first.setPosition(window.getSize().x / 6.0f * 2.0f, titleText.getPosition().y + 200 + (i * 60));
    highscoresTextsVector[i].second.setPosition(window.getSize().x / 6.0f * 4.0f, titleText.getPosition().y + 200 + (i * 60));
  }

  /* Add color to the first 3 places */
  if(highscoresTextsVector.size() >= 1){
    highscoresTextsVector[0].first.setFillColor(sf::Color(255, 215, 0));
    highscoresTextsVector[0].second.setFillColor(sf::Color(255, 215, 0));
  }
  if(highscoresTextsVector.size() >= 2) {
    highscoresTextsVector[1].first.setFillColor(sf::Color(192, 192, 192));
    highscoresTextsVector[1].second.setFillColor(sf::Color(192, 192, 192));
  }
  if(highscoresTextsVector.size() >= 3) {
    highscoresTextsVector[2].first.setFillColor(sf::Color(205, 127, 50));
    highscoresTextsVector[2].second.setFillColor(sf::Color(205, 127, 50));
  }
}

void HighscoresScene::update(Game &game, sf::RenderWindow &window) {
  /* Set buttons color on hover*/
  goToMenuButton.update(window);
  cleanHighscoresButton.update(window);

  /* Check for keyboard or mouse button press events */
  checkEvents(game, window);
}

void HighscoresScene::checkEvents(Game& game, sf::RenderWindow& window) {
  if (goToMenuButton.isClicked(sceneEvent, window)) {
    game.changeScene(new MenuScene(game, window, sceneFont));
    return;
  }
  if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
    game.changeScene(new MenuScene(game, window, sceneFont));
    return;
  }
  if (cleanHighscoresButton.isClicked(sceneEvent, window)) {
    game.getHighscores().cleanHighscores();
    game.changeScene(new HighscoresScene(game, window, sceneFont));
    return;
  }
}

void HighscoresScene::processEvent(sf::Event &ev) {
  sceneEvent = ev;
}

void HighscoresScene::drawIn (sf::RenderWindow &window) {
  window.draw(titleText);
  for (size_t i = 0; i < highscoresTextsVector.size(); i++){
    window.draw(highscoresTextsVector[i].first);
    window.draw(highscoresTextsVector[i].second);
  }
  goToMenuButton.drawIn(window);
  cleanHighscoresButton.drawIn(window);
}