#include "Button.h"
#include "iostream"
#include <string>

Button::Button(std::string btnText, sf::Font* gameFont, std::string size){
  /* Set up button text */
  this->buttonText.setFont(*gameFont);
  this->buttonText.setCharacterSize(36);
  this->buttonText.setString(btnText);
  this->buttonText.setFillColor(sf::Color::White);

  /* If button size is auto, the size its the text size + 20, if the size its a number, the button size is the given number*/
  if(size == "auto") {
    this->buttonBox.setSize({buttonText.getGlobalBounds().getSize().x + 20, 50});
  } else {
    this->buttonBox.setSize({std::stof(size), 50.0f});
  }

  /* Set up button box */
  this->buttonBox.setFillColor(sf::Color::Transparent);
  this->buttonBox.setOutlineThickness(2);
  this->buttonBox.setOutlineColor(sf::Color::White);
  this->buttonBox.setOrigin(this->buttonBox.getSize().x / 2.0f, this->buttonBox.getSize().y / 2.0f);
  this->buttonText.setOrigin(this->buttonText.getGlobalBounds().width / 2.0f, this->buttonText.getGlobalBounds().height / 2.0f);
}

void Button::update(sf::RenderWindow &window) {
  /* Change the color of the button if the mouse is inside it */
  if(this->isMouseContained(window)) {
    this->buttonText.setFillColor(sf::Color::Red);
  } else {
    this->buttonText.setFillColor(sf::Color::White);
  }
}

void Button::setPos(sf::Vector2f pos) {
  this->buttonText.setPosition({ pos.x, pos.y - 10});
  this->buttonBox.setPosition({pos.x, pos.y});
}

bool Button::isClicked(sf::Event &evt, sf::RenderWindow &window) {
  if (evt.type == sf::Event::MouseButtonPressed) {
    if (evt.mouseButton.button == sf::Mouse::Left && this->isMouseContained(window) && window.hasFocus()) {
      return true;
    }
  }
  return false;
}

bool Button::isMouseContained(sf::RenderWindow &window) {
  /* Transform the mouse position into coords and check if its contained into the button box */
  sf::Vector2i mousePos(sf::Mouse::getPosition(window));
  sf::Vector2f mousePosInView = window.mapPixelToCoords(mousePos);
  if(buttonBox.getGlobalBounds().contains(mousePosInView)){
    return true;
  }
  return false;
}

sf::Vector2f Button::getSize() {
  return this->buttonBox.getGlobalBounds().getSize();
}

sf::RectangleShape& Button::getBox() {
  return this->buttonBox;
}


void Button::drawIn(sf::RenderWindow &window) {
  window.draw(this->buttonText);
  window.draw(this->buttonBox);
}