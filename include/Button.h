#pragma once
#include <SFML/Graphics.hpp>

class Button {
  private:
    sf::Text buttonText;
    sf::RectangleShape buttonBox;
  public:
    Button(std::string btnText, sf::Font* gameFont, std::string size = "280");
    void update(sf::RenderWindow &window);
    void setPos(sf::Vector2f pos);
    sf::RectangleShape& getBox();
    bool isMouseContained(sf::RenderWindow &window);
    bool isClicked(sf::RenderWindow &window);
    sf::Vector2f getSize();
    void drawIn(sf::RenderWindow &window);
    ~Button() {};
};