#include "Hud.h"

Hud::Hud (sf::Font &font)
    : fuelCH4Indicator(font, "CH4", 100)
    , fuelLOXIndicator(font, "LOX", 350) {
}

void Hud::update(Ship *ship, sf::View &view) {
  fuelCH4Indicator.update(ship->getCH4());
  fuelLOXIndicator.update(ship->getLOX());
  fuelCH4Indicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 100});
  fuelLOXIndicator.setPos({view.getCenter().x + view.getSize().x / 2.0f - 100, view.getCenter().y + view.getSize().y / 2.0f - 150});
}

void Hud::draw(sf::RenderWindow &window){
  fuelCH4Indicator.draw(window);
  fuelLOXIndicator.draw(window);
}