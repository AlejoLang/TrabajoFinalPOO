#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "PlayScene.h"
#include "MenuScene.h"

class Game {
  private:
    sf::RenderWindow window;
    Scene *currentScene;
    Scene *nextScene;
  public:
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    void changeScene(Scene *newScene);
    ~Game();
};

#endif