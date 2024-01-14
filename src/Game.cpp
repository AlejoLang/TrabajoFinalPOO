#include "Game.h"
#include "Scene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include <string>
#include <ctime>

Game::Game() 
    : window(sf::VideoMode(1920, 1080), "Juego", sf::Style::Fullscreen )
    , gameVolume(100)
    , gameHighscores ("./resources/Highscores.dat")
{
  if(!gameFont.loadFromFile("./resources/fonts/RetroGaming.ttf")) { exit(1); }
  setUsername("Player");
  window.setFramerateLimit(60);
  currentScene = new MenuScene(*this, window, &gameFont);
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
    } else {
      currentScene->processEvent(evt);
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

int Game::getGameDifficulty() {
  return this->gameDifficulty;
}

void Game::setGameDifficulty(int newDifficulty) {
  this->gameDifficulty = newDifficulty;
}

int Game::getGameVolume() {
  return this->gameVolume;
}

void Game::setGameVolume(int newVolume) {
  this->gameVolume = newVolume;
}

std::string Game::getUsername()
{
    return this->username;
}

void Game::setUsername(std::string newUsername)
{
    this->username = newUsername;
}

Highscore& Game::getHighscores()
{
    return gameHighscores;
}

void Game::changeScene(Scene *newScene) {
  nextScene = newScene;
}

Game::~Game() {
  delete currentScene;
}