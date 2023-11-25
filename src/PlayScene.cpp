#include <SFML/Graphics.hpp>
#include "PlayScene.h"

PlayScene::PlayScene(sf::RenderWindow &window) 
          : mainMap(window)
          , mainView(window.getDefaultView())
          , playerShip(window)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  playerShip.setTexture(playerTexture);
}

void PlayScene::update() {
  playerShip.update(mainMap);
  mainView.setCenter(playerShip.getCenter().x, playerShip.getCenter().y - 350.f);
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  playerShip.drawIn(window);
  mainMap.drawIn(window);
}