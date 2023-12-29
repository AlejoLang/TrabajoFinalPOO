#include "Button.h"
#include <iostream>

Button::Button(std::string btnText){
  this->buttonFont.loadFromFile("./resources/fonts/RetroGaming.ttf");
  this->buttonText.setFont(buttonFont);
  this->buttonText.setCharacterSize(36);
  this->buttonText.setString(btnText);
  this->buttonText.setColor(sf::Color::White);
  this->buttonText.setOrigin(this->buttonText.getGlobalBounds().width / 2.0f, this->buttonText.getGlobalBounds().height / 2.0f);
  this->buttonBox.setSize({280, 50});
  this->buttonBox.setFillColor(sf::Color::Transparent);
  this->buttonBox.setOutlineThickness(2);
  this->buttonBox.setOutlineColor(sf::Color::White);
  this->buttonBox.setOrigin(this->buttonBox.getSize().x / 2.0f, this->buttonBox.getSize().y / 2.0f);
}

void Button::update(sf::RenderWindow &window) {
  if(this->isMouseContained(window)) {
    this->buttonText.setColor(sf::Color::Red);
  } else {
    this->buttonText.setColor(sf::Color::White);
  }
}

void Button::setPos(sf::Vector2f pos) {
  this->buttonText.setPosition(pos);
  this->buttonBox.setPosition({pos.x, pos.y + 10});
}

bool Button::isClicked(sf::RenderWindow &window) {
  if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && this->isMouseContained(window)) {
    return true;
  }
  return false;
}

bool Button::isMouseContained(sf::RenderWindow &window) {
  sf::Vector2i mousePos(sf::Mouse::getPosition(window));
  sf::Vector2f mousePosInView = window.mapPixelToCoords(mousePos);
  if(buttonBox.getGlobalBounds().contains(mousePosInView)){
    return true;
  }
  return false;
}

void Button::drawIn(sf::RenderWindow &window) {
  window.draw(this->buttonText);
  window.draw(this->buttonBox);
}