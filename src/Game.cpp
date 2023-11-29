#include "Game.h"
#include <ctime>

Game::Game() 
    : window(sf::VideoMode(1920, 1080), "Juego")
{
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  if(!gameFont.loadFromFile("./resources/fonts/Roboto-Regular.ttf")){exit(1);}
  currentScene = new MenuScene(gameFont);
  nextScene = nullptr;
  srand(time(NULL));
}

void Game::Run() {
  while (window.isOpen()) {
    handleEvents();
    Update();
    Draw();
    if(nextScene != nullptr) {
      delete currentScene;
      currentScene = nextScene;
      nextScene = nullptr;
    }
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
  currentScene->update(*this, window);
}

void Game::Draw() {
  window.clear();
  currentScene->drawIn(window);
  window.display();
}

void Game::changeScene(Scene *newScene) {
  nextScene = newScene;
}

Game::~Game() {
  delete currentScene;
}