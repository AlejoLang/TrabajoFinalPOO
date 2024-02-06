#pragma once

#include <SFML/Graphics.hpp>

namespace GetGap {
  template <typename T> sf::Vector2f getCenter(T& origin);
  template <typename T, typename S> sf::Vector2f getPlaceBelow(T& origin, S& toPlace, float gap);
  template <typename T, typename S> sf::Vector2f getPlaceRight(T& origin, S& toPlace, float gap);
  template <typename T> sf::Vector2f getPlaceRight(T& origin, float gap);
}