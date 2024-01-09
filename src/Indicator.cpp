#include "Indicator.h"
#include <string>

Indicator::Indicator(std::string text, float base, sf::Font* gameFont) {
  indicatorText.setFont(*gameFont);
  indicatorText.setString(text);
  indicatorText.setOrigin({0, indicatorText.getGlobalBounds().width / 2.0f});
  indicatorRect.setFillColor(sf::Color::White);
  indicatorRectOut.setOutlineColor(sf::Color::White);
  indicatorRectOut.setFillColor(sf::Color::Transparent);
  indicatorRectOut.setOutlineThickness(3);
  baseMagnitude = base;
  value = 100;
}

void Indicator::update(float newValue) {
  setValue(newValue);
}

void Indicator::setValue(float newValue) {
  newValue = std::max(0.0f, std::min(newValue, baseMagnitude));
  indicatorRect.setSize({-(newValue * (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness())) / baseMagnitude, indicatorRect.getGlobalBounds().getSize().y}); 
  value = newValue;
}

void Indicator::setSize(sf::Vector2f newSize) {
  indicatorRect.setSize({newSize.x, newSize.y});
  indicatorRect.setOrigin({0, indicatorRect.getSize().y / 2.0f});
  indicatorRectOut.setSize({newSize.x, newSize.y});
  indicatorRectOut.setOrigin({0, indicatorRectOut.getSize().y / 2.0f});
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
  indicatorText.setPosition(pos);
  indicatorRect.setPosition(pos.x -= 10, pos.y - indicatorText.getGlobalBounds().height / 2.0f - 2);
  indicatorRectOut.setPosition(indicatorRect.getPosition().x, indicatorRect.getPosition().y);
}

void Indicator::draw(sf::RenderWindow &window) {
  window.draw(indicatorText);
  window.draw(indicatorRect);
  window.draw(indicatorRectOut);
}