#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Game.h"
#include "Scene.h"
#include "DeathScene.h"
#include "Ship.h"
#include "Hud.h"
#include "Map.h"
#include "ObstaclesCollection.h"
#include "FuelRefillerCollection.h"

class PlayScene : public Scene {
  private:
    sf::View mainView;
    sf::Texture playerTexture;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Ship *playerShip;
    Map mainMap;
    Hud mainHud;
    ObstaclesCollection mainObstaclesCollection;
    FuelRefillerCollection mainRefillerCollection;
    int deadFrameCount;
    int points;
  public:
    PlayScene(sf::RenderWindow &window, sf::Font* gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    void updateBackground(float altitude);
    void updatePoints();
    void reducePoints(float val);
    void updateGameDifficulty(Game &game, float altitude);
    ~PlayScene();
};

#endif