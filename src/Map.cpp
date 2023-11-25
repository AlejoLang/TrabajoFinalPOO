#include <SFML/Graphics.hpp>
#include "Map.h"

Map::Map(sf::RenderWindow &window) {
  if(!groundTexture.loadFromFile("./resources/textures/Ground.png")) {exit(1); }
  if(!launchPadTexture.loadFromFile("./resources/textures/Launchpad.png")) {exit(1); }
  if(!launchPadTowerTexture.loadFromFile("./resources/textures/padTower.png")) {exit(1); }

  groundTexture.setRepeated(true);
  ground.setTexture(groundTexture);
  ground.setTextureRect({0, 0, window.getSize().x * 5, 100});
  ground.setPosition(-ground.getTextureRect().getSize().x / 2.0f, window.getSize().y - 100);
  
  launchPad.setTexture(launchPadTexture);
  launchPad.setOrigin(launchPadTexture.getSize().x / 2.0f, launchPadTexture.getSize().y);
  launchPad.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100);
  
  launchPadTower.setTexture(launchPadTowerTexture);
  launchPadTower.setPosition(launchPad.getPosition().x - 14 - launchPadTexture.getSize().x / 2, launchPad.getPosition().y - launchPadTowerTexture.getSize().y);
}

bool Map::checkCollision(sf::Sprite &sprite) {
  if(ground.getGlobalBounds().intersects(sprite.getGlobalBounds()) 
    || launchPad.getGlobalBounds().intersects(sprite.getGlobalBounds())) 
  {
    return true;
  }
  return false;
}

void Map::drawIn(sf::RenderWindow &window) {
  window.draw(ground);
  window.draw(launchPad);
  window.draw(launchPadTower);
}