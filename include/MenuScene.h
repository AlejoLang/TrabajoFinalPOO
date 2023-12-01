#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"

class MenuScene : public Scene{
  private:
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Font menuFont;
    sf::Clock timer;
    int countdownHours = 24;
    int countdownMinutes = 0;
    int countdownSeconds = 0;
  public:
    MenuScene();
    void update(Game &game, sf::RenderWindow &window) override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif 