#pragma once

#include <SFML/Graphics.hpp>

template <typename T> sf::Vector2f getCenter(T& object) {
  return { object.getGlobalBounds().getSize().x / 2.0f, object.getGlobalBounds().getSize().y / 2.0f };
};

template <typename T> sf::Vector2f getDeviation(T& object) {
  /* Gets the difference between the origin of an object and its center */
  float dx = object.getOrigin().x - object.getGlobalBounds().getSize().x / 2.0f;
  float dy = object.getOrigin().y - object.getGlobalBounds().getSize().y / 2.0f;
  return { dx, dy };
};

template <typename T, typename S> sf::Vector2f getPlaceBelow(T& origin, S& toPlace, float gap) {
  sf::Vector2f deviationOrigin = getDeviation<T>(origin);
  sf::Vector2f deviationToPlace = getDeviation<S>(toPlace);
  sf::Vector2f position = { origin.getPosition().x - deviationOrigin.x, origin.getPosition().y - deviationOrigin.y };
  position.y += (origin.getGlobalBounds().height / 2.0f) + (toPlace.getGlobalBounds().height / 2.0f) + gap;
  position += deviationToPlace;
  return position;
};

template <typename T, typename S> sf::Vector2f getPlaceRight(T& origin, S& toPlace, float gap) {
  sf::Vector2f deviationOrigin = getDeviation<T>(origin);
  sf::Vector2f deviationToPlace = getDeviation<S>(toPlace);
  sf::Vector2f position = { origin.getPosition().x - deviationOrigin.x, origin.getPosition().y - deviationOrigin.y };
  position.x += (origin.getGlobalBounds().width / 2.0f) + (toPlace.getGlobalBounds().width / 2.0f) + gap;
  position += deviationToPlace;
  return position;
};

template <typename T, typename S> sf::Vector2f getPlaceAbove(T& origin, S& toPlace, float gap) {
  sf::Vector2f deviationOrigin = getDeviation<T>(origin);
  sf::Vector2f deviationToPlace = getDeviation<S>(toPlace);
  sf::Vector2f position = { origin.getPosition().x - deviationOrigin.x, origin.getPosition().y - deviationOrigin.y };
  position.y -= (origin.getGlobalBounds().height / 2.0f) + (toPlace.getGlobalBounds().height / 2.0f) + gap;
  position += deviationToPlace;
  return position;
};

template <typename T, typename S> sf::Vector2f getPlaceLeft(T& origin, S& toPlace, float gap) {
  sf::Vector2f deviationOrigin = getDeviation<T>(origin);
  sf::Vector2f deviationToPlace = getDeviation<S>(toPlace);
  sf::Vector2f position = { origin.getPosition().x - deviationOrigin.x, origin.getPosition().y - deviationOrigin.y };
  position.x -= (origin.getGlobalBounds().width / 2.0f) + (toPlace.getGlobalBounds().width / 2.0f) + gap;
  position += deviationToPlace;
  return position;
};