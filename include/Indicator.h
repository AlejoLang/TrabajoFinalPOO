#pragma once
#include <SFML/Graphics.hpp>

class Indicator
{
  protected:
    sf::Text indicatorText;
    sf::RectangleShape indicatorRect;
    sf::RectangleShape indicatorRectOut;
    std::string textPos;
    float baseMagnitude;
    float value;
  public:
    Indicator(std::string text, std::string txtPos, float base, sf::Font* gameFont);
    void update(float newValue);
    void setSize(sf::Vector2f newSize);
    void setValue(float newValue);
    void setInsideColor(sf::Color color);
    void setBorderColor(sf::Color color);
    float getValuePercentaje();
    void setPos(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
    ~Indicator() {};
};