#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Highscore.h"
class Scene;

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