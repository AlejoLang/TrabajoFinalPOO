#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Highscore.h"

class HighscoresScene : public Scene {
  private:
    std::vector<std::pair <sf::Text, sf::Text>> highscoresTextsVector;
    sf::Text titleText;
    sf::Text headerText;
    Button goToMenuButton;
    Button cleanHighscoresButton;
  public:
    HighscoresScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont);
    void setUpHighscoresText(Game &game, sf::RenderWindow &window);
    void update(Game &game, sf::RenderWindow &window) override;
    void checkEvents(Game& game, sf::RenderWindow& window);
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    ~HighscoresScene() {};
};