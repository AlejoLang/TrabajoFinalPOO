#ifndef INDICATOR_H
#define INDICATOR_H
#include <SFML/Graphics.hpp>
#include <string>

class Indicator
{
  private:
    sf::Text indicatorText;
    sf::RectangleShape indicatorRect;
    sf::RectangleShape indicatorRectOut;
    float baseMagnitude;
  public:
    Indicator(std::string text, float base, sf::Font* gameFont);
    void update(float value);
    void setPos(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
};

#endif