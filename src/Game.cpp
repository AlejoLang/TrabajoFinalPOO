#include "Game.h"
#include <ctime>

Game::Game() 
    : window(sf::VideoMode(1920, 1080), "Juego")
{
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  if(!gameFont.loadFromFile("./resources/fonts/Roboto-Regular.ttf")){exit(1);}
  currentScene = new PlayScene(window, gameFont);
  nextScene = nullptr;
  srand(time(NULL));
}

void Game::Run() {
  while (window.isOpen()) {
    handleEvents();
    Update();
    Draw();
  }
}

void Game::handleEvents() {
  sf::Event evt;
  while (window.pollEvent(evt)) {
    if (evt.type == sf::Event::Closed) {
      window.close();
    }
  }
}

void Game::Update() {
  currentScene->update();
}

void Game::Draw() {
  window.clear();
  /*Draw Section*/
  currentScene->drawIn(window);
  window.display();
}

Game::~Game() {
  
}