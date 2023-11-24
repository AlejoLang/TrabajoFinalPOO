#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include <SFML/Graphics.hpp>
#include "Scene.h"

class PlayScene : public Scene {
  private:
  public:
    PlayScene();
    void update() override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif