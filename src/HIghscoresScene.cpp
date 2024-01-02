#include "HighscoresScene.h"
#include <iostream>

HighscoresScene::HighscoresScene(sf::RenderWindow &window, Highscore &highscores, sf::Font* gameFont)
                :Scene(gameFont)
                , goToMenuButton("Menu", gameFont)
                , cleanHighscoresButton("Clean Highscores", gameFont, "auto")
{
  titleText.setFont(*sceneFont);
  titleText.setString("Highscores");
  titleText.setCharacterSize(72);
  titleText.setOrigin(titleText.getGlobalBounds().getSize().x / 2.0, titleText.getGlobalBounds().getSize().y / 2.0);
  titleText.setPosition(window.getSize().x / 2.0, 100);
  setUpHighscoresText(window, highscores);
  goToMenuButton.setPos({window.getSize().x / 2.0, window.getSize().y - 100});
  cleanHighscoresButton.setPos({window.getSize().x - (cleanHighscoresButton.getSize().x / 2.0) - 100, window.getSize().y - 100});
}

void HighscoresScene::setUpHighscoresText(sf::RenderWindow &window, Highscore &highscores) {
  std::vector <HighscoreStruct> hsVector = highscores.getHighscores();
  sf::Text auxName;
  sf::Text auxPoints;
  auxName.setFont(*sceneFont);
  auxPoints.setFont(*sceneFont);
  auxName.setCharacterSize(32);
  auxPoints.setCharacterSize(32);
  for (size_t i = 0; i < hsVector.size(); i++) {
    auxName.setString((std::string)hsVector[i].username);
    auxPoints.setString(std::to_string(hsVector[i].points));
    highscoresTextsVector.push_back({auxName, auxPoints});
    highscoresTextsVector[i].first.setOrigin(0, highscoresTextsVector[i].first.getGlobalBounds().getSize().y / 2.0);
    highscoresTextsVector[i].second.setOrigin(highscoresTextsVector[i].second.getGlobalBounds().getSize().x , highscoresTextsVector[i].second.getGlobalBounds().getSize().y / 2.0);
    highscoresTextsVector[i].first.setPosition(window.getSize().x / 2.0 - (32 * 10), 300 + (i * 60));
    highscoresTextsVector[i].second.setPosition(window.getSize().x / 2.0 + (32 * 10), 300 + (i * 60));
  }
  if(highscoresTextsVector.size() >= 1){
    highscoresTextsVector[0].first.setColor(sf::Color(255, 215, 0));
    highscoresTextsVector[0].second.setColor(sf::Color(255, 215, 0));
  }
  if(highscoresTextsVector.size() >= 2) {
    highscoresTextsVector[1].first.setColor(sf::Color(192, 192, 192));
    highscoresTextsVector[1].second.setColor(sf::Color(192, 192, 192));
  }
  if(highscoresTextsVector.size() >= 3) {
    highscoresTextsVector[2].first.setColor(sf::Color(205, 127, 50));
    highscoresTextsVector[2].second.setColor(sf::Color(205, 127, 50));
  }
}

void HighscoresScene::update(Game &game, sf::RenderWindow &window) {
  goToMenuButton.update(window);
  cleanHighscoresButton.update(window);
  if(goToMenuButton.isClicked(window)) {
    game.changeScene(new MenuScene(game, window, sceneFont));
  }/**/
  if (sceneEvent.key.code == sf::Keyboard::Escape) {
    game.changeScene(new MenuScene(game, window, sceneFont));
  }
  if(cleanHighscoresButton.isClicked(window)) {
    game.gameHighscores.cleanHighscores();
    game.changeScene(new HighscoresScene(window, game.gameHighscores, sceneFont));
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