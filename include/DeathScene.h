#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "Button.h"
class Game;
class Scene;

class DeathScene : public Scene{
  private:
    sf::Font sceneFont;
    sf::Text mainText;
    sf::Text pointsText;
    Button backToMenu;
    Button restartGame;
  public:
    DeathScene(sf::RenderWindow &window, int points);
    void update(Game &game, sf::RenderWindow &window) override;
    void drawIn(sf::RenderWindow &window) override;
};