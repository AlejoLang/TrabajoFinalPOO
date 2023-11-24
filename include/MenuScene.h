#ifndef MENUSCENE_H
#define MENUSCENE_H
#include <SFML/Graphics.hpp>
#include "Scene.h"

class MenuScene : public Scene{
  private:
  public:
    MenuScene();
    void update() override;
    void drawIn(sf::RenderWindow &window) override;
};

#endif 