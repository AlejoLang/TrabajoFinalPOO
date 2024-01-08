#pragma once
#include <SFML/Graphics.hpp>
#include "Indicator.h"

class Selector : public Indicator {
  public:
    Selector(std::string text, sf::Font* gameFont);
    void update(sf::RenderWindow &window);
    void setValue(float newValue);
    void setSize(sf::Vector2f newSize);
    void setPos(sf::Vector2f pos);
    void setValuePercentaje(float newValue);
    void checkMousePositionInSelector(sf::RenderWindow &window);
};