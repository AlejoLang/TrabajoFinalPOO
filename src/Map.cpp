#include <SFML/Graphics.hpp>
#include "Map.h"

Map::Map(sf::RenderWindow &window) {
  /* Load textures */
  if(!groundTexture.loadFromFile("./resources/textures/Ground.png")) {exit(1); }
  if(!launchPadTexture.loadFromFile("./resources/textures/Launchpad.png")) {exit(1); }
  if(!launchPadTowerTexture.loadFromFile("./resources/textures/padTower.png")) {exit(1); }

  /* Set ground sprite */
  groundTexture.setRepeated(true);
  ground.setTexture(groundTexture);
  ground.setTextureRect({0, 0, int(window.getSize().x) * 5, int(groundTexture.getSize().y)});
  ground.setPosition(-ground.getTextureRect().getSize().x / 2.0f, 0.0f);
  
  /* Set launchpad sprite */
  launchPad.setTexture(launchPadTexture);
  launchPad.setOrigin(launchPadTexture.getSize().x / 2.0f, launchPadTexture.getSize().y);
  launchPad.setPosition(window.getSize().x / 2.0f, 0);
  
  /* Set launchpad tower */
  launchPadTower.setTexture(launchPadTowerTexture);
  launchPadTower.setPosition(launchPad.getPosition().x - 14.0f - launchPadTexture.getSize().x / 2.0f, launchPad.getPosition().y - launchPadTowerTexture.getSize().y);
}


sf::Sprite Map::getGroundSprite() {
  return this->ground;
}

sf::Sprite& Map::getLaunchPadSprite() {
  return this->launchPad;
}

void Map::drawIn(sf::RenderWindow &window) {
  window.draw(ground);
  window.draw(launchPad);
  window.draw(launchPadTower);
}