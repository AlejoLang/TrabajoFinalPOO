#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "Highscore.h"
#include <string>

class Game {
  private:
    sf::RenderWindow window;
    Scene *currentScene;
    Scene *nextScene;
    sf::Font gameFont;
  public:
    Highscore gameHighscores;
    std::string username;
    bool isFocused;
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    void changeScene(Scene *newScene);
    ~Game();
};

#endif