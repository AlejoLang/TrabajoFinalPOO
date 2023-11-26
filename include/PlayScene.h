#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "Scene.h"
#include "Ship.h"
#include "Hud.h"
#include "Map.h"
#include "Asteroid.h"

class PlayScene : public Scene {
  private:
    sf::View mainView;
    sf::Texture playerTexture;
    sf::Texture backgroundTexture;
    sf::Sprite background;
    Ship *playerShip;
    Map mainMap;
    Hud mainHud;
    std::vector<Asteroid *> asteroidsVector;
    std::vector<sf::Texture> asteroidTexures;
    sf::Clock asteroidGenerationClock; 
    float asteroidGenerationTime;
  public:
    PlayScene(sf::RenderWindow &window, sf::Font &gameFont);
    void update() override;
    void handleAsteroidsGeneration();
    void handleAsteroidsDraw(sf::RenderWindow &window);
    void drawIn(sf::RenderWindow &window) override;
    ~PlayScene();
};

#endif