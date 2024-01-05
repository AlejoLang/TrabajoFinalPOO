#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iomanip>
#include "Game.h"
#include "Scene.h"
#include "Button.h"
#include "Highscore.h"

class HighscoresScene : public Scene{
  private:
    std::vector<std::pair <sf::Text, sf::Text>> highscoresTextsVector;
    sf::Text titleText;
    sf::Text headerText;
    Button goToMenuButton;
    Button cleanHighscoresButton;
  public:
    HighscoresScene(sf::RenderWindow &window, Highscore &highscores, sf::Font* gameFont);
    void setUpHighscoresText(sf::RenderWindow &window, Highscore &highscores);
    void update(Game &game, sf::RenderWindow &window) override;
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    ~HighscoresScene() {};
};