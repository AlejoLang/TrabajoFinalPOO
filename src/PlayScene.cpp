#include <SFML/Graphics.hpp>
#include "PlayScene.h"

PlayScene::PlayScene(){
  if(!playerTexture.loadFromFile("./resources/textures/Starship.png")){ exit(1); }
  playerShip.setTexture(playerTexture);
}

void PlayScene::update() {
  playerShip.update();
}

void PlayScene::drawIn(sf::RenderWindow &window) {
  playerShip.drawIn(window);
}