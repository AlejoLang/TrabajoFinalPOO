#ifndef HUD_H
#define HUD_H
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Indicator.h"

class Hud {
  private:
    Indicator fuelLOXIndicator;
    Indicator fuelCH4Indicator;
    sf::Text velocityText;
    sf::Text velocityUnitsText;
    float velocityTextPadd;
    sf::Text altitudeText;
    sf::Text altitudeUnitsText;
    float altitudeTextPadd;
  public:
    Hud(sf::Font* gameFont);
    void update(Ship *playerShip, sf::View &view);
    void updateIndicators(Ship *playerShip, sf::View &view);
    void updateAltitudeText(Ship *playerShip, sf::View &view);
    void updateVelocityText(Ship *playerShip, sf::View &view);
    void draw(sf::RenderWindow &window);
    ~Hud() {};
};

#endif