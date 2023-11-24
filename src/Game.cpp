#include "Game.h"

Game::Game() 
    : window(sf::VideoMode(1280, 720), "Juego")
{
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  currentScene = new MenuScene;
  nextScene = nullptr;
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