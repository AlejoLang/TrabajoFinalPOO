#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Highscore.h"
class Scene;
#include "iostream"

template <typename T> sf::Vector2f getCenter(T &origin){
  return {origin.getGlobalBounds().getSize().x / 2.0f, origin.getGlobalBounds().getSize().y / 2.0f};
};

template <typename T, typename S> sf::Vector2f getPlaceBelow(T &origin, S &toPlace, float gap){
  return {origin.getPosition().x, origin.getPosition().y + (origin.getGlobalBounds().getSize().y / 2.0f) + (toPlace.getGlobalBounds().getSize().y / 2.0f) + gap};
};
template <typename T, typename S> sf::Vector2f getPlaceRight(T &origin, S &toPlace, float gap){
  return {origin.getPosition().x + (origin.getGlobalBounds().getSize().x / 2.0f) + (toPlace.getGlobalBounds().getSize().x / 2.0f) + gap, origin.getPosition().y};
};
template <typename T> sf::Vector2f getPlaceRight(T &origin, float gap){
  return {origin.getPosition().x + (origin.getGlobalBounds().getSize().x / 2.0f) + gap, origin.getPosition().y};
};

class Game {
  private:
    sf::RenderWindow window;
    Scene *currentScene;
    Scene *nextScene;
    sf::Font gameFont;
    int gameDifficulty;
    int gameVolume;
  public:
    Highscore gameHighscores;
    std::string username;
    bool isFocused;
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    int getGameDifficulty();
    void setGameDifficulty(int newDifficulty);
    int getGameVolume();
    void setGameVolume(int newVolume);
    void changeScene(Scene *newScene);
    ~Game();
};

#endif