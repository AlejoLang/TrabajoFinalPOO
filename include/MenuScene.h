#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "Button.h"

class MenuScene : public Scene{
  private:
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Font menuFont;
    sf::Clock timer;
    int countdownHours = 24;
    int countdownMinutes = 0;
    int countdownSeconds = 0;
    Button goToPlayButton;
    Button exitButton;
  public:
    MenuScene(sf::RenderWindow &window);
    void update(Game &game, sf::RenderWindow &window) override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif 