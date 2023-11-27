#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Scene.h"
#include "Ship.h"
#include "Hud.h"
#include "Map.h"
#include "AsteroidCollection.h"

class PlayScene : public Scene {
  private:
    sf::View mainView;
    sf::Texture playerTexture;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Ship *playerShip;
    Map mainMap;
    Hud mainHud;
    AsteroidCollection mainAsteroidCollection;
  public:
    PlayScene(sf::RenderWindow &window, sf::Font &gameFont);
    void update() override;
    void drawIn(sf::RenderWindow &window) override;
    ~PlayScene();
};

#endif