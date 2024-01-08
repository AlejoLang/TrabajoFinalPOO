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
    void updateIndicators(float LOXLevel, float CH4Level , sf::View &view);
    void updateAltitudeText(float altitude, sf::View &view);
    void updateVelocityText(float velocity, sf::View &view);
    void draw(sf::RenderWindow &window);
    ~Hud() {};
};

#endif