#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "PlayScene.h"
#include "HighscoresScene.h"
#include "Button.h"
#include "InputBox.h"

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
    Button goToHighscoresButton;
  public:
    MenuScene(sf::RenderWindow &window, sf::Font* gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif 