#include <SFML/Graphics.hpp>
#include "PlayScene.h"

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font &gameFont) 
          : mainMap(window)
          , mainView(window.getDefaultView())
          , playerShip(window)
          , mainHud(gameFont)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  if(!backgroundTexture.loadFromFile("./resources/textures/Background.png")) { exit(1); }
  playerShip.setTexture(playerTexture);
  background.setTexture(backgroundTexture);
  background.setOrigin(backgroundTexture.getSize().x / 2.0f, backgroundTexture.getSize().y / 2.0f);
}

void PlayScene::update() {
  playerShip.update(mainMap);
  mainView.setCenter(playerShip.getCenter().x, playerShip.getCenter().y - 350.f);
  mainHud.update(playerShip, mainView);
  background.setPosition(mainView.getCenter());
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  window.draw(background);
  playerShip.drawIn(window);
  mainMap.drawIn(window);
  mainHud.draw(window);
}