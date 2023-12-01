#include "Indicator.h"
#include <iostream>

Indicator::Indicator(sf::Font &textFont, std::string text, float base) {
  indicatorText.setFont(textFont);
  indicatorText.setString(text);
  indicatorText.setOrigin({0, indicatorText.getGlobalBounds().width / 2.0f});
  indicatorRect.setFillColor(sf::Color::White);
  indicatorRect.setSize({-200, 10});
  indicatorRect.setOrigin({0, indicatorRect.getSize().y / 2.0f});
  indicatorRectOut.setOutlineColor(sf::Color::Blue);
  indicatorRectOut.setFillColor(sf::Color::Transparent);
  indicatorRectOut.setOutlineThickness(3);
  indicatorRectOut.setSize({-200, 10});
  indicatorRectOut.setOrigin({0, indicatorRectOut.getSize().y / 2.0f});
  baseMagnitude = base;
}

void Indicator::update(float val) {
  indicatorRect.setSize({-(val * 200) / baseMagnitude, 10});
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