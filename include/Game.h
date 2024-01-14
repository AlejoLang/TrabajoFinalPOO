#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Highscore.h"
class Scene;

template <typename T> sf::Vector2f getCenter(T &origin){
  return {origin.getGlobalBounds().getSize().x / 2.0f, origin.getGlobalBounds().getSize().y / 2.0f};
};

template <typename T, typename S> sf::Vector2f getPlaceBelow(T &origin, S &toPlace, float gap){
  return {origin.getPosition().x, origin.getPosition().y + (origin.getGlobalBounds().height / 2.0f) + (toPlace.getGlobalBounds().height / 2.0f) + gap};
};
template <typename T, typename S> sf::Vector2f getPlaceRight(T &origin, S &toPlace, float gap){
  return {origin.getPosition().x + (origin.getGlobalBounds().width  / 2.0f) + (toPlace.getGlobalBounds().width / 2.0f) + gap, origin.getPosition().y};
};
template <typename T> sf::Vector2f getPlaceRight(T &origin, float gap){
  return {origin.getPosition().x + (origin.getGlobalBounds().getSize().x / 2.0f) + gap, origin.getPosition().y};
};

class Game {
  private:
    sf::RenderWindow window;
    sf::Font gameFont;
    Scene* currentScene;
    Scene* nextScene;
    Highscore gameHighscores;
    int gameDifficulty;
    float gameVolume;
    std::string username;
  public:
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    int getGameDifficulty();
    void setGameDifficulty(int newDifficulty);
    float getGameVolume();
    void setGameVolume(float newVolume);
    std::string getUsername();
    void setUsername(std::string newUsername);
    Highscore& getHighscores();
    void changeScene(Scene *newScene);
    ~Game();
};

#endif