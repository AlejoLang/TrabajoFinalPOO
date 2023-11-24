#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <Scene.h>
#include <PlayScene.h>
#include <MenuScene.h>

class Game {
  private:
    sf::RenderWindow window;
    sf::Font gameFont;
    Scene *currentScene;
    Scene *nextScene;
  public:
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    ~Game();
};

#endif