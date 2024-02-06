#include "Scene.h"
#include "InstructionsScene.h"
#include "PlayScene.h"
#include "MenuScene.h"
#include "GetGap.h"

InstructionsScene::InstructionsScene(sf::RenderWindow &window, sf::Font* gameFont) : Scene (gameFont) {
  setUpImages(window);
  setUpText(window);
}

void InstructionsScene::setUpImages(sf::RenderWindow &window) {
  /* Load textures*/
  if(!wKeypadTexture.loadFromFile("./resources/textures/wKeypad.png")) {exit(1);}
  if(!arrowKeypadsTexture.loadFromFile("./resources/textures/arrowKeypads.png")) {exit(1);}
  if(!escKeypadTexture.loadFromFile("./resources/textures/escKeypad.png")) {exit(1);}
  if(!LOXRefillerTexture.loadFromFile("./resources/textures/LOXRefiller.png")) {exit(1);}
  if(!CH4RefillerTexture.loadFromFile("./resources/textures/CH4Refiller.png")) {exit(1);}
  if(!asteroidTexture.loadFromFile("./resources/textures/Asteroid2.png")) {exit(1);}
  if(!airplaneTexture.loadFromFile("./resources/textures/Airplane1.png")) {exit(1);}
  
  /* Set textures in sprites */
  wKeypadSprite.setTexture(wKeypadTexture);
  arrowKeypadsSprite.setTexture(arrowKeypadsTexture);
  escKeypadSprite.setTexture(escKeypadTexture);
  LOXRefillerSprite.setTexture(LOXRefillerTexture);
  CH4RefillerSprite.setTexture(CH4RefillerTexture);
  asteroidSprite.setTexture(asteroidTexture);
  airplaneSprite.setTexture(airplaneTexture);

  /* Set sprites origin */
  wKeypadSprite.setOrigin(getCenter(wKeypadSprite));
  arrowKeypadsSprite.setOrigin(getCenter(arrowKeypadsSprite));
  escKeypadSprite.setOrigin(getCenter(escKeypadSprite));
  LOXRefillerSprite.setOrigin(getCenter(LOXRefillerSprite));
  CH4RefillerSprite.setOrigin(getCenter(CH4RefillerSprite));
  asteroidSprite.setOrigin(getCenter(asteroidSprite));
  airplaneSprite.setOrigin(getCenter(airplaneSprite));

  /* Set sprites position */
  wKeypadSprite.setPosition(200, 300);
  arrowKeypadsSprite.setPosition(getPlaceBelow(wKeypadSprite, arrowKeypadsSprite, 100));
  escKeypadSprite.setPosition(getPlaceBelow(arrowKeypadsSprite, escKeypadSprite,100));
  LOXRefillerSprite.setPosition((window.getSize().x / 2.0f) + 200, 300);
  CH4RefillerSprite.setPosition(getPlaceRight(LOXRefillerSprite, CH4RefillerSprite, 20));
  asteroidSprite.setPosition(getPlaceBelow(LOXRefillerSprite, asteroidSprite, 100));
  airplaneSprite.setPosition(getPlaceRight(asteroidSprite, airplaneSprite, 20));
}

void InstructionsScene::setUpText(sf::RenderWindow &window) {
  /* Set texts font */
  titleText.setFont(*sceneFont);
  accelerateInstructionText.setFont(*sceneFont);
  rotateInstructionText.setFont(*sceneFont);
  quitInstructionText.setFont(*sceneFont);
  avoidInstructionText.setFont(*sceneFont);
  collectInstructionText.setFont(*sceneFont);
  continueText.setFont(*sceneFont);

  /* Set texts string */
  titleText.setString("Instructions");
  accelerateInstructionText.setString("Press to accelerate");
  rotateInstructionText.setString("Press to rotate");
  quitInstructionText.setString("Press to go to Menu\n(Points not saved)");
  avoidInstructionText.setString("Avoid the obstacles");
  collectInstructionText.setString("Collect to gain fuel");
  continueText.setString("Press Enter to continue...");

  /* Set cheracter size */
  titleText.setCharacterSize(48);
  accelerateInstructionText.setCharacterSize(24);
  rotateInstructionText.setCharacterSize(24);
  quitInstructionText.setCharacterSize(24);
  avoidInstructionText.setCharacterSize(24);
  collectInstructionText.setCharacterSize(24);
  continueText.setCharacterSize(36);

  /* Set texts origin */
  titleText.setOrigin(titleText.getGlobalBounds().getSize().x / 2.0f, titleText.getGlobalBounds().getSize().y / 2.0f);
  accelerateInstructionText.setOrigin(0, accelerateInstructionText.getGlobalBounds().getSize().y / 2.0f);
  rotateInstructionText.setOrigin(0, rotateInstructionText.getGlobalBounds().getSize().y / 2.0f);
  quitInstructionText.setOrigin(0, quitInstructionText.getGlobalBounds().getSize().y / 2.0f);
  avoidInstructionText.setOrigin(0, avoidInstructionText.getGlobalBounds().getSize().y / 2.0f);
  collectInstructionText.setOrigin(0, collectInstructionText.getGlobalBounds().getSize().y / 2.0f);
  continueText.setOrigin(continueText.getGlobalBounds().getSize().x / 2.0f, continueText.getGlobalBounds().getSize().y / 2.0f );

  /* Set texts position */
  titleText.setPosition(window.getSize().x / 2.0f, 100);
  accelerateInstructionText.setPosition(getPlaceRight(wKeypadSprite, 50));
  rotateInstructionText.setPosition(getPlaceRight(arrowKeypadsSprite, 50));
  quitInstructionText.setPosition(getPlaceRight(escKeypadSprite, 50));
  avoidInstructionText.setPosition(getPlaceRight(airplaneSprite, 50));
  collectInstructionText.setPosition(getPlaceRight(CH4RefillerSprite, 50));
  continueText.setPosition(window.getSize().x / 2.0f, (window.getSize().y - 100.0f));
}

void InstructionsScene::update(Game &game, sf::RenderWindow &window) { 
  /* Make the text blink */
  if(int(timer.getElapsedTime().asSeconds()*3)%2) {
    continueText.setString("");
  } else {
    continueText.setString("Press Enter to continue...");
  }

  /* Check for keyboard or mouse button press events */
  checkEvents(game, window);
}

void InstructionsScene::checkEvents(Game& game, sf::RenderWindow& window) {
  if (sceneEvent.type == sf::Event::KeyReleased) {
    if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
      game.changeScene(new MenuScene(game, window, sceneFont));
      return;
    }
    if (sceneEvent.key.scancode == sf::Keyboard::Scan::Enter) {
      game.changeScene(new PlayScene(game, window, sceneFont));
      return;
    }
  }
}

void InstructionsScene::processEvent(sf::Event &ev) {
  sceneEvent = ev;
}

void InstructionsScene::drawIn(sf::RenderWindow &window) {
    window.draw(wKeypadSprite);
    window.draw(arrowKeypadsSprite);
    window.draw(escKeypadSprite);
    window.draw(asteroidSprite);
    window.draw(airplaneSprite);
    window.draw(LOXRefillerSprite);
    window.draw(CH4RefillerSprite);
    window.draw(titleText);
    window.draw(accelerateInstructionText);
    window.draw(rotateInstructionText);
    window.draw(quitInstructionText);
    window.draw(avoidInstructionText);
    window.draw(collectInstructionText);
    window.draw(continueText);
}

InstructionsScene::~InstructionsScene() {}