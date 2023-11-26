#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Ship.h"
#include "Hud.h"
#include "Map.h"

class PlayScene : public Scene {
  private:
    sf::View mainView;
    sf::Texture playerTexture;
    sf::Texture asteroidTexture;
    Ship playerShip;
    Map mainMap;
    Hud mainHud;
  public:
    PlayScene(sf::RenderWindow &window, sf::Font &gameFont);
    void update() override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif