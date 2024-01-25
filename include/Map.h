#pragma once
#include <SFML/Graphics.hpp>

class Map
{
  private:
    sf::Texture groundTexture;
    sf::Texture launchPadTexture;
    sf::Texture launchPadTowerTexture;
    sf::Sprite ground;
    sf::Sprite launchPad;
    sf::Sprite launchPadTower;
  public:
    Map(sf::RenderWindow &window);
    void drawIn(sf::RenderWindow &window);
    sf::Sprite getGroundSprite();
    sf::Sprite& getLaunchPadSprite();
    ~Map() {};
};