#include "HighscoresScene.h"
#include <iostream>

HighscoresScene::HighscoresScene(sf::RenderWindow &window, Highscore &highscores) 
  : goToMenuButton("Menu")
{
  if(!sceneFont.loadFromFile("./resources/fonts/RetroGaming.ttf")) { exit(1); }
  titleText.setFont(sceneFont);
  titleText.setString("Highscores");
  titleText.setCharacterSize(72);
  titleText.setOrigin(titleText.getGlobalBounds().getSize().x / 2.0, titleText.getGlobalBounds().getSize().y / 2.0);
  titleText.setPosition(window.getSize().x / 2.0, 100);
  setUpHighscoresText(window, highscores);
  goToMenuButton.setPos({window.getSize().x / 2.0, window.getSize().y - 100});
}

void HighscoresScene::setUpHighscoresText(sf::RenderWindow &window, Highscore &highscores) {
  std::vector <HighscoreStruct> hsVector = highscores.getHighscores();
  std::cout<<hsVector.size()<<std::endl;
  sf::Text aux;
  aux.setFont(sceneFont);
  aux.setCharacterSize(32);
  std::stringstream stream;
  for (size_t i = 0; i < hsVector.size(); i++) {
    stream.str("");
    stream << std::fixed << hsVector[i].username << std::setw(30) << std::setfill(' ') <<hsVector[i].points;
    aux.setString(stream.str());
    highscoresTextsVector.push_back(aux);
    highscoresTextsVector[i].setOrigin(highscoresTextsVector[i].getGlobalBounds().getSize().x / 2.0, highscoresTextsVector[i].getGlobalBounds().getSize().y / 2.0);
    highscoresTextsVector[i].setPosition(window.getSize().x / 2.0, 300 + (i * 60));
  }
  if(highscoresTextsVector.size() >= 1){
    highscoresTextsVector[0].setColor(sf::Color(255, 215, 0));
  }
  if(highscoresTextsVector.size() >= 2) {
    highscoresTextsVector[1].setColor(sf::Color(192, 192, 192));
  }
  if(highscoresTextsVector.size() >= 3) {
    highscoresTextsVector[2].setColor(sf::Color(205, 127, 50));
  }
}

void HighscoresScene::update(Game &game, sf::RenderWindow &window) {
  goToMenuButton.update(window);
  if(goToMenuButton.isClicked(window)) {
    game.changeScene(new MenuScene(window));
  }
}

void HighscoresScene::drawIn (sf::RenderWindow &window) {
  window.draw(titleText);
  for (size_t i = 0; i < highscoresTextsVector.size(); i++){
    window.draw(highscoresTextsVector[i]);
  }
  goToMenuButton.drawIn(window);
}