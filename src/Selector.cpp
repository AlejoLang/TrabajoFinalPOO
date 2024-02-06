#include "Selector.h"

Selector::Selector(std::string text, std::string txtPos, sf::Font* gameFont) : Indicator(text, txtPos, 100, gameFont) {

}

void Selector::update(sf::RenderWindow &window) {
  if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window.hasFocus()) {
    checkMousePositionInSelector(window);
  }
}

void Selector::setValue(float newValue) {
  /* Adjust the indicator box to the given value*/
  newValue = std::max(0.0f, std::min(newValue, baseMagnitude));
  indicatorRect.setSize({(newValue * (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness())) / baseMagnitude, indicatorRect.getGlobalBounds().getSize().y}); 
  value = newValue;
}

void Selector::setValuePercentaje(float newValue) {
  /* Transform the porcentaje to a value and the adjust the indicator box */
  newValue = (newValue * baseMagnitude) / 100;
  this->setValue(newValue);
}

void Selector::checkMousePositionInSelector(sf::RenderWindow &window) {
  /* Get the mouse distance from the left of the selection box*/
  float mouseRelativePosition = value;
  sf::Vector2i mousePos(sf::Mouse::getPosition(window));
  sf::Vector2f mousePosInView = window.mapPixelToCoords(mousePos);
  if(indicatorRectOut.getGlobalBounds().contains(mousePosInView)){
    mouseRelativePosition = mousePosInView.x - indicatorRectOut.getGlobalBounds().left;
    this->setValue((mouseRelativePosition * baseMagnitude) / (indicatorRectOut.getGlobalBounds().getSize().x - indicatorRectOut.getOutlineThickness()));
  }
}