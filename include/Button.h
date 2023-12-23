#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button {
  private:
    sf::Text buttonText;
    sf::Font buttonFont;
    sf::RectangleShape buttonBox;
  public:
    Button(std::string btnText);
    void update(sf::RenderWindow &window);
    void setPos(sf::Vector2f pos);
    bool isMouseContained(sf::RenderWindow &window);
    bool isClicked(sf::RenderWindow &window);
    void drawIn(sf::RenderWindow &window);
};