#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Ship.h"

class PlayScene : public Scene {
  private:
    sf::View mainView;
    sf::Texture playerTexture;
    sf::Texture asteroidTexture;
    Ship playerShip;
  public:
    PlayScene();
    void update() override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif