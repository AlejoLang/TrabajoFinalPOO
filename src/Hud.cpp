#include "Hud.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

Hud::Hud (sf::Font* gameFont)
    : fuelLOXIndicator("LOX", 350, gameFont) 
    , fuelCH4Indicator("CH4", 100, gameFont)
{
  altitudeText.setString("Altitude: 0000.00");
  altitudeText.setFont(*gameFont);
  altitudeText.setCharacterSize(24);
  altitudeText.setOrigin({0, altitudeText.getGlobalBounds().height / 2.0f});
  altitudeUnitsText.setString("Km");
  altitudeUnitsText.setFont(*gameFont);
  altitudeUnitsText.setCharacterSize(24);
  altitudeUnitsText.setOrigin({0, altitudeUnitsText.getGlobalBounds().height / 2.0f});
  altitudeTextPadd = altitudeText.getGlobalBounds().width;
  velocityText.setString("Velocity: 0000.00");
  velocityText.setFont(*gameFont);
  velocityText.setCharacterSize(24);
  velocityText.setOrigin({0, velocityText.getGlobalBounds().height / 2.0f});
  velocityUnitsText.setString("Km/H");
  velocityUnitsText.setFont(*gameFont);
  velocityUnitsText.setCharacterSize(24);
  velocityUnitsText.setOrigin({0, velocityText.getGlobalBounds().height / 2.0f});
  velocityTextPadd = velocityText.getGlobalBounds().width;
}

void Hud::update(Ship *playerShip, sf::View &view) {
  updateIndicators(playerShip, view);
  updateAltitudeText(playerShip, view);
  updateVelocityText(playerShip, view);
}

void Hud::updateIndicators(Ship *playerShip, sf::View &view) {
  fuelCH4Indicator.update(playerShip->getCH4());
  fuelCH4Indicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 100});
  fuelLOXIndicator.update(playerShip->getLOX());
  fuelLOXIndicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 150});
}

void Hud::updateAltitudeText(Ship *playerShip, sf::View &view) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << std::setw(7) << std::setfill('0') << playerShip->getAltitudeKm();
  std::string alt = stream.str();
  altitudeText.setString("Altitude: " + alt);
  altitudeText.setPosition({view.getCenter().x - view.getSize().x / 2.0f + 30, view.getCenter().y + view.getSize().y / 2.0f - 100});
  altitudeUnitsText.setPosition(altitudeText.getPosition().x + altitudeTextPadd + 10, altitudeText.getPosition().y);
}

void Hud::updateVelocityText(Ship *playerShip, sf::View &view) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << std::setw(7) << std::setfill('0') << playerShip->getVelocityKm_H();
  std::string alt = stream.str();
  velocityText.setString("Velocity: " + alt);
  velocityText.setPosition({view.getCenter().x - view.getSize().x / 2.0f + 30, view.getCenter().y + view.getSize().y / 2.0f - 150});
  velocityUnitsText.setPosition(velocityText.getPosition().x + velocityTextPadd + 10, velocityText.getPosition().y);
}

void Hud::draw(sf::RenderWindow &window){
  fuelCH4Indicator.draw(window);
  fuelLOXIndicator.draw(window);
  window.draw(altitudeText);
  window.draw(velocityText);
  window.draw(altitudeUnitsText);
  window.draw(velocityUnitsText);
}