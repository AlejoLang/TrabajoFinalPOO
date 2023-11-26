#include <SFML/Graphics.hpp>
#include "PlayScene.h"

PlayScene::PlayScene(sf::RenderWindow &window, sf::Font &gameFont) 
          : mainMap(window)
          , mainView(window.getDefaultView())
          , playerShip(window)
          , mainHud(gameFont)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  playerShip.setTexture(playerTexture);
}

void PlayScene::update() {
  playerShip.update(mainMap);
  mainView.setCenter(playerShip.getCenter().x, playerShip.getCenter().y - 350.f);
  mainHud.update(playerShip, mainView);
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  window.setView(mainView);
  playerShip.drawIn(window);
  mainMap.drawIn(window);
  mainHud.draw(window);
}