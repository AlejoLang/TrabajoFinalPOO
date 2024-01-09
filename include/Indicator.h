#ifndef INDICATOR_H
#define INDICATOR_H
#include <SFML/Graphics.hpp>

class Indicator
{
  protected:
    sf::Text indicatorText;
    sf::RectangleShape indicatorRect;
    sf::RectangleShape indicatorRectOut;
    float baseMagnitude;
    float value;
  public:
    Indicator(std::string text, float base, sf::Font* gameFont);
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

#endif