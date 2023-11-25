#include <SFML/Graphics.hpp>
#include "Map.h"

Map::Map(sf::RenderWindow &window) {
  if(!groundTexture.loadFromFile("./resources/textures/Ground.png")) {exit(1); }
  if(!launchPadTexture.loadFromFile("./resources/textures/Launchpad.png")) {exit(1); }
  groundTexture.setRepeated(true);
  ground.setTexture(groundTexture);
  launchPad.setTexture(launchPadTexture);
  ground.setTextureRect({0, 0, window.getSize().x, 100});
  ground.setPosition(0, window.getSize().y - 100);
  launchPad.setOrigin(launchPadTexture.getSize().x / 2.0f, launchPadTexture.getSize().y);
  launchPad.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100);
}

bool Map::checkCollision(sf::Sprite &sprite) {
  if(ground.getGlobalBounds().intersects(sprite.getGlobalBounds()) 
    /*|| padCollider.getGlobalBounds().intersects(sprite.getGlobalBounds())*/) 
  {
    return true;
  }
  return false;
}

void Map::drawIn(sf::RenderWindow &window) {
  window.draw(ground);
  window.draw(launchPad);
}