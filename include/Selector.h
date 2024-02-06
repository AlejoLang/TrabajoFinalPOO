#pragma once
#include <SFML/Graphics.hpp>
#include "Indicator.h"

class Selector : public Indicator {
  public:
    Selector(std::string text, std::string, sf::Font* gameFont);
    void update(sf::RenderWindow &window);
    void setValue(float newValue);
    void setValuePercentaje(float newValue);
    void checkMousePositionInSelector(sf::RenderWindow &window);
};