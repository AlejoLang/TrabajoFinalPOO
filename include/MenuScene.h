#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "InputBox.h"
#include "Selector.h"

class MenuScene : public Scene{
  private:
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Font menuFont;
    sf::Clock timer;
    int countdownHours = 24;
    int countdownMinutes = 0;
    int countdownSeconds = 0;
    InputText nameInput;
    Button goToPlayButton;
    Button exitButton;
    Button goToHighscoresButton;
    Selector volumeSelector;
  public:
    MenuScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    ~MenuScene() {};
};

#endif 