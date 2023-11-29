#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
class Game;
class Scene;

class MenuScene : public Scene{
  private:
    sf::Font menuFont;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Clock timer;
    int countdownHours = 24;
    int countdownMinutes = 0;
    int countdownSeconds = 0;
  public:
    MenuScene(sf::Font &gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif 