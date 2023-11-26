#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Indicator.h"

class Hud {
  private:
    Indicator fuelLOXIndicator;
    Indicator fuelCH4Indicator;
  public:
    Hud(sf::Font &font);
    void update(Ship *ship, sf::View &view);
    void draw(sf::RenderWindow &window);
};

#endif