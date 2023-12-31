#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "Highscore.h"
#include <cstring>

class Game {
  private:
    sf::RenderWindow window;
    Scene *currentScene;
    Scene *nextScene;
    sf::Font gameFont;
  public:
    Highscore gameHighscores;
    char username[20];
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    void changeScene(Scene *newScene);
    ~Game();
};

#endif