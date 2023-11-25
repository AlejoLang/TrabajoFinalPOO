#include <SFML/Graphics.hpp>
#include "PlayScene.h"

PlayScene::PlayScene(sf::RenderWindow &window) 
          : mainMap(window)
{
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  playerShip.setTexture(playerTexture);
}

void PlayScene::update() {
  playerShip.update(mainMap);
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  mainMap.drawIn(window);
  playerShip.drawIn(window);
}