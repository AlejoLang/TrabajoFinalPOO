#include "Indicator.h"
#include "GetGap.h"
#include <string>

Indicator::Indicator(std::string text, std::string txtPos, float base, sf::Font* gameFont) {
  /* Set up text */
  indicatorText.setFont(*gameFont);
  indicatorText.setString(text);
  indicatorText.setCharacterSize(24);
  indicatorText.setOrigin({indicatorText.getGlobalBounds().width / 2.0f, indicatorText.getGlobalBounds().height / 2.0f});

  /* Set up rectangles */
  indicatorRect.setFillColor(sf::Color::White);
  indicatorRectOut.setOutlineColor(sf::Color::White);
  indicatorRectOut.setFillColor(sf::Color::Transparent);
  indicatorRectOut.setOutlineThickness(3);

  /* Set up variables */
  baseMagnitude = base;
  value = 100;
  textPos = txtPos;
}

void Indicator::update(float newValue) {
  setValue(newValue);
}

void Indicator::setValue(float newValue) {
  newValue = std::max(0.0f, std::min(newValue, baseMagnitude));
  indicatorRect.setSize({(newValue * (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness())) / baseMagnitude, indicatorRect.getGlobalBounds().getSize().y}); 
  value = newValue;
}

void Indicator::setSize(sf::Vector2f newSize) {
  indicatorRectOut.setSize({newSize.x, newSize.y});
  indicatorRectOut.setOrigin({ newSize.x / 2.0f, newSize.y / 2.0f  });
  indicatorRect.setSize({ newSize.x, newSize.y });
  indicatorRect.setOrigin(indicatorRectOut.getOrigin());
}

void Indicator::setInsideColor(sf::Color color) {
  indicatorRect.setFillColor(color);
}
void Indicator::setBorderColor(sf::Color color) {
  indicatorRectOut.setOutlineColor(color);
}

float Indicator::getValuePercentaje() {
  return ((this->value * 100) / baseMagnitude);
}

void Indicator::setPos(sf::Vector2f pos) {
  indicatorRectOut.setPosition(pos);
  indicatorRect.setPosition(pos);
  if (textPos == "above") {
    indicatorText.setPosition(getPlaceAbove(indicatorRectOut, indicatorText, 20));
  } else if (textPos == "below") {
    indicatorText.setPosition(getPlaceBelow(indicatorRectOut, indicatorText, 20));
  } else if (textPos == "right") {
    indicatorText.setPosition(getPlaceRight(indicatorRectOut, indicatorText, 20));
    indicatorText.setPosition(indicatorText.getPosition().x, indicatorText.getPosition().y - (indicatorText.getCharacterSize() / 4));
  } else if (textPos == "left") {
    indicatorText.setPosition(getPlaceLeft(indicatorRectOut, indicatorText, 20));
    indicatorText.setPosition(indicatorText.getPosition().x, indicatorText.getPosition().y - (indicatorText.getCharacterSize() / 4));
  } else {
    indicatorText.setPosition(getPlaceAbove(indicatorRectOut, indicatorText, 20));
  }
}

void Indicator::draw(sf::RenderWindow &window) {
  window.draw(indicatorText);
  window.draw(indicatorRect);
  window.draw(indicatorRectOut);
}