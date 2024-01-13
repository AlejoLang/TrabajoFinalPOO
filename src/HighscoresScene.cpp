#include "Game.h"
#include "Scene.h"
#include "HighscoresScene.h"
#include "MenuScene.h"
#include <vector>
#include <string>
#include <iomanip>

HighscoresScene::HighscoresScene(sf::RenderWindow &window, Highscore &highscores, sf::Font* gameFont)
                :Scene(gameFont)
                , goToMenuButton("Menu", gameFont)
                , cleanHighscoresButton("Clean Highscores", gameFont, "auto")
{
  titleText.setFont(*sceneFont);
  titleText.setString("Highscores");
  titleText.setCharacterSize(72);
  titleText.setOrigin(getCenter(titleText));
  titleText.setPosition({window.getSize().x / 2.0f, 100.0f});
  setUpHighscoresText(window, highscores);
  goToMenuButton.setPos({window.getSize().x / 2.0f, window.getSize().y - 100.0f});
  cleanHighscoresButton.setPos(getPlaceRight(goToMenuButton.getBox(), cleanHighscoresButton.getBox(), 300));
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
    highscoresTextsVector[i].first.setOrigin(getCenter(highscoresTextsVector[i].first));
    highscoresTextsVector[i].second.setOrigin(getCenter(highscoresTextsVector[i].second));
    highscoresTextsVector[i].first.setPosition(window.getSize().x / 6.0f * 2.0f, titleText.getPosition().y + 200 + (i * 60));
    highscoresTextsVector[i].second.setPosition(window.getSize().x / 6.0f * 4.0f, titleText.getPosition().y + 200 + (i * 60));
  }
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
  goToMenuButton.update(window);
  cleanHighscoresButton.update(window);
  if(goToMenuButton.isClicked(sceneEvent, window)) {
    game.changeScene(new MenuScene(game, window, sceneFont));
    return;
  }
  if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
    game.changeScene(new MenuScene(game, window, sceneFont));
    return;
  }
  if(cleanHighscoresButton.isClicked(sceneEvent, window)) {
    game.gameHighscores.cleanHighscores();
    game.changeScene(new HighscoresScene(window, game.gameHighscores, sceneFont));
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