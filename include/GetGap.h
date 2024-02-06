#pragma once

#include <SFML/Graphics.hpp>

template <typename T> sf::Vector2f getCenter(T& origin) {
  return { origin.getGlobalBounds().getSize().x / 2.0f, origin.getGlobalBounds().getSize().y / 2.0f };
};

template <typename T, typename S> sf::Vector2f getPlaceBelow(T& origin, S& toPlace, float gap) {
  return { origin.getPosition().x, origin.getPosition().y + (origin.getGlobalBounds().height / 2.0f) + (toPlace.getGlobalBounds().height / 2.0f) + gap };
};

template <typename T, typename S> sf::Vector2f getPlaceRight(T& origin, S& toPlace, float gap) {
  return { origin.getPosition().x + (origin.getGlobalBounds().width / 2.0f) + (toPlace.getGlobalBounds().width / 2.0f) + gap, origin.getPosition().y };
};

template <typename T> sf::Vector2f getPlaceRight(T& origin, float gap) {
  return { origin.getPosition().x + (origin.getGlobalBounds().getSize().x / 2.0f) + gap, origin.getPosition().y };
};