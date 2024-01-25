#pragma once
#include <SFML/Graphics.hpp>
#include "Hud.h"
#include "Map.h"
#include "ObstaclesCollection.h"
#include "FuelRefillerCollection.h"
class Ship;

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
    PlayScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont);
    void update(Game &game, sf::RenderWindow &window) override;
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    void updateBackground(float altitude);
    void updatePoints();
    void reducePoints(float val);
    void updateGameDifficulty(Game &game, float altitude);
    ~PlayScene();
};