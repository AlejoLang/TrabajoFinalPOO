#pragma once
#include <SFML/Graphics.hpp>
#include "Highscore.h"
class Scene;

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