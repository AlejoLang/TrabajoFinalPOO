#include "Selector.h"

#include <iostream>
Selector::Selector(std::string text, sf::Font* gameFont) : Indicator(text, 200, gameFont) {
  indicatorText.setOrigin({indicatorText.getGlobalBounds().getSize().x / 2.0f, indicatorText.getGlobalBounds().getSize().y / 2.0f});
}

void Selector::update(sf::RenderWindow &window) {
  if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    checkMousePositionInSelector(window);
  }
}

void Selector::setSize(sf::Vector2f newSize) {
  indicatorRect.setSize({newSize.x, newSize.y});
  indicatorRect.setOrigin({indicatorRect.getSize().x / 2.0f, indicatorRect.getSize().y / 2.0f});
  indicatorRectOut.setSize({newSize.x, newSize.y});
  indicatorRectOut.setOrigin({indicatorRectOut.getSize().x / 2.0f, indicatorRectOut.getSize().y / 2.0f});
}

void Selector::setPos(sf::Vector2f pos) {
  indicatorText.setPosition(pos.x, pos.y - (indicatorText.getGlobalBounds().getSize().y / 2.0f) - 10);
  indicatorRect.setPosition(pos.x, pos.y + (indicatorRect.getGlobalBounds().getSize().y / 2.0f) + 10);
  indicatorRectOut.setPosition(indicatorRect.getPosition().x, indicatorRect.getPosition().y);
}

void Selector::setValue(float newValue) {
  newValue = std::max(0.0f, std::min(newValue, baseMagnitude));
  indicatorRect.setSize({(newValue * (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness())) / baseMagnitude, indicatorRect.getGlobalBounds().getSize().y}); 
  value = newValue;
}

void Selector::setValuePercentaje(float newValue) {
  newValue = (newValue * (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness())) / 100;
  this->setValue(newValue);
}

void Selector::checkMousePositionInSelector(sf::RenderWindow &window) {
  float mouseRelativePosition = value;
  sf::Vector2i mousePos(sf::Mouse::getPosition(window));
  sf::Vector2f mousePosInView = window.mapPixelToCoords(mousePos);
  if(indicatorRectOut.getGlobalBounds().contains(mousePosInView)){
    mouseRelativePosition = mousePosInView.x - indicatorRectOut.getGlobalBounds().left;
  }
  this->setValue(mouseRelativePosition);
}