#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

class Game {
  private:
    sf::RenderWindow window;
  public:
    Game();
    void Run();
    void handleEvents();
    void Update();
    void Draw();
    ~Game();
};

#endif