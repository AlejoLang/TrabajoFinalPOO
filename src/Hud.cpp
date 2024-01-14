#include "Hud.h"
#include "Ship.h"
#include <string>
#include <sstream>
#include <iomanip>

Hud::Hud (sf::Font* gameFont)
    : fuelLOXIndicator("LOX", 350, gameFont) 
    , fuelCH4Indicator("CH4", 100, gameFont)
{
  /* Set up altitude text */
  altitudeText.setString("Altitude: 0000.00");
  altitudeText.setFont(*gameFont);
  altitudeText.setCharacterSize(24);
  altitudeText.setOrigin({0, altitudeText.getGlobalBounds().height / 2.0f});

  /* Set up altitude units text */
  altitudeUnitsText.setString("Km");
  altitudeUnitsText.setFont(*gameFont);
  altitudeUnitsText.setCharacterSize(24);
  altitudeUnitsText.setOrigin({0, altitudeUnitsText.getGlobalBounds().height / 2.0f});
  altitudeTextPadd = altitudeText.getGlobalBounds().width;

  /* Set up velocity text */
  velocityText.setString("Velocity: 0000.00");
  velocityText.setFont(*gameFont);
  velocityText.setCharacterSize(24);
  velocityText.setOrigin({0, velocityText.getGlobalBounds().height / 2.0f});

  /* Set up velocity units text */
  velocityUnitsText.setString("Km/H");
  velocityUnitsText.setFont(*gameFont);
  velocityUnitsText.setCharacterSize(24);
  velocityUnitsText.setOrigin({0, velocityText.getGlobalBounds().height / 2.0f});
  velocityTextPadd = velocityText.getGlobalBounds().width;

  /* Set up indicators */
  fuelCH4Indicator.setSize({-200, 10});
  fuelLOXIndicator.setSize({-200, 10});
  fuelCH4Indicator.setBorderColor(sf::Color::Red);
  fuelLOXIndicator.setBorderColor(sf::Color::Red);
}

void Hud::update(Ship *playerShip, sf::View &view) {
  updateIndicators(playerShip->getLOX(), playerShip->getCH4(), view);
  updateAltitudeText(playerShip->getAltitudeKm(), view);
  updateVelocityText(playerShip->getVelocityKm_H(), view);
}

void Hud::updateIndicators(float LOXLevel, float CH4Level, sf::View &view) {
  /* Update indicator using the player fuel levels */
  fuelCH4Indicator.update(CH4Level);
  fuelCH4Indicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 100});
  fuelLOXIndicator.update(LOXLevel);
  fuelLOXIndicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 150});
}

void Hud::updateAltitudeText(float altitude, sf::View &view) {
  /* Update altitude using iomanip to get a fixed string size */
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << std::setw(7) << std::setfill('0') << altitude;
  std::string alt = stream.str();
  altitudeText.setString("Altitude: " + alt);
  altitudeText.setPosition({view.getCenter().x - view.getSize().x / 2.0f + 30, view.getCenter().y + view.getSize().y / 2.0f - 100});
  altitudeUnitsText.setPosition(altitudeText.getPosition().x + altitudeTextPadd + 10, altitudeText.getPosition().y);
}

void Hud::updateVelocityText(float velocity, sf::View &view) {
  /* Update velocity using iomanip to get a fixed string size */
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << std::setw(7) << std::setfill('0') << velocity;
  std::string alt = stream.str();
  velocityText.setString("Velocity: " + alt);
  velocityText.setPosition({view.getCenter().x - view.getSize().x / 2.0f + 30, view.getCenter().y + view.getSize().y / 2.0f - 150});
  velocityUnitsText.setPosition(velocityText.getPosition().x + velocityTextPadd + 10, velocityText.getPosition().y);
}

void Hud::draw(sf::RenderWindow &window){
  window.draw(altitudeText);
  window.draw(velocityText);
  window.draw(altitudeUnitsText);
  window.draw(velocityUnitsText);
  fuelCH4Indicator.draw(window);
  fuelLOXIndicator.draw(window);
}