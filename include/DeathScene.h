#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Highscore.h"

class DeathScene : public Scene {
  private:
    sf::Text mainText;
    sf::Text pointsText;
    Button backToMenu;
    Button restartGame;
  public:
    DeathScene(Game &game, sf::RenderWindow &window, int points, sf::Font* gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void checkEvents(Game& game, sf::RenderWindow& window);
    void processEvent(sf::Event &ev) override;
    void updateHighscores(Game &game, int points);
    void drawIn(sf::RenderWindow &window) override;
    ~DeathScene() {};
};