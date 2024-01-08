#include "InstructionsScene.h"

InstructionsScene::InstructionsScene(Game &game, sf::RenderWindow &window, sf::Font* gameFont) : Scene (gameFont) {
  setUpImages(window);
  setUpText(window);
}

void InstructionsScene::setUpImages(sf::RenderWindow &window) {
  if(!wKeypadTexture.loadFromFile("./resources/textures/wKeypad.png")) {exit(1);}
  if(!arrowKeypadsTexture.loadFromFile("./resources/textures/arrowKeypads.png")) {exit(1);}
  if(!escKeypadTexture.loadFromFile("./resources/textures/escKeypad.png")) {exit(1);}
  if(!LOXRefillerTexture.loadFromFile("./resources/textures/LOXRefiller.png")) {exit(1);}
  if(!CH4RefillerTexture.loadFromFile("./resources/textures/CH4Refiller.png")) {exit(1);}
  if(!asteroidTexture.loadFromFile("./resources/textures/Asteroid2.png")) {exit(1);}
  if(!airplaneTexture.loadFromFile("./resources/textures/Airplane1.png")) {exit(1);}
  
  wKeypadSprite.setTexture(wKeypadTexture);
  arrowKeypadsSprite.setTexture(arrowKeypadsTexture);
  escKeypadSprite.setTexture(escKeypadTexture);
  LOXRefillerSprite.setTexture(LOXRefillerTexture);
  CH4RefillerSprite.setTexture(CH4RefillerTexture);
  asteroidSprite.setTexture(asteroidTexture);
  airplaneSprite.setTexture(airplaneTexture);

  wKeypadSprite.setOrigin(getCenter(wKeypadSprite));
  arrowKeypadsSprite.setOrigin(getCenter(arrowKeypadsSprite));
  escKeypadSprite.setOrigin(getCenter(escKeypadSprite));
  LOXRefillerSprite.setOrigin(getCenter(LOXRefillerSprite));
  CH4RefillerSprite.setOrigin(getCenter(CH4RefillerSprite));
  asteroidSprite.setOrigin(getCenter(asteroidSprite));
  airplaneSprite.setOrigin(getCenter(airplaneSprite));

  wKeypadSprite.setPosition(200, 300);
  arrowKeypadsSprite.setPosition(getPlaceBelow(wKeypadSprite, arrowKeypadsSprite, 100));
  escKeypadSprite.setPosition(getPlaceBelow(arrowKeypadsSprite, escKeypadSprite,100));
  LOXRefillerSprite.setPosition((window.getSize().x / 2.0f) + 200, 300);
  CH4RefillerSprite.setPosition(getPlaceRight(LOXRefillerSprite, CH4RefillerSprite, 20));
  asteroidSprite.setPosition(getPlaceBelow(LOXRefillerSprite, asteroidSprite, 100));
  airplaneSprite.setPosition(getPlaceRight(asteroidSprite, airplaneSprite, 20));
}

void InstructionsScene::setUpText(sf::RenderWindow &window) {
  titleText.setFont(*sceneFont);
  accelerateInstructionText.setFont(*sceneFont);
  rotateInstructionText.setFont(*sceneFont);
  quitInstructionText.setFont(*sceneFont);
  avoidInstructionText.setFont(*sceneFont);
  collectInstructionText.setFont(*sceneFont);
  continueText.setFont(*sceneFont);

  titleText.setString("Instructions");
  accelerateInstructionText.setString("Press to accelerate");
  rotateInstructionText.setString("Press to rotate");
  quitInstructionText.setString("Press to go to Menu\n(Points not saved)");
  avoidInstructionText.setString("Avoid the obstacles");
  collectInstructionText.setString("Collect to gain fuel");
  continueText.setString("Press any key to continue...");

  titleText.setCharacterSize(48);
  accelerateInstructionText.setCharacterSize(24);
  rotateInstructionText.setCharacterSize(24);
  quitInstructionText.setCharacterSize(24);
  avoidInstructionText.setCharacterSize(24);
  collectInstructionText.setCharacterSize(24);
  continueText.setCharacterSize(36);

  titleText.setOrigin(titleText.getGlobalBounds().getSize().x / 2.0f, titleText.getGlobalBounds().getSize().y / 2.0f);
  accelerateInstructionText.setOrigin(0, accelerateInstructionText.getGlobalBounds().getSize().y / 2.0f);
  rotateInstructionText.setOrigin(0, rotateInstructionText.getGlobalBounds().getSize().y / 2.0f);
  quitInstructionText.setOrigin(0, quitInstructionText.getGlobalBounds().getSize().y / 2.0f);
  avoidInstructionText.setOrigin(0, avoidInstructionText.getGlobalBounds().getSize().y / 2.0f);
  collectInstructionText.setOrigin(0, collectInstructionText.getGlobalBounds().getSize().y / 2.0f);
  continueText.setOrigin(continueText.getGlobalBounds().getSize().x / 2.0f, continueText.getGlobalBounds().getSize().y / 2.0f );

  titleText.setPosition(window.getSize().x / 2.0f, 100);
  accelerateInstructionText.setPosition(getPlaceRight(wKeypadSprite, 50));
  rotateInstructionText.setPosition(getPlaceRight(arrowKeypadsSprite, 50));
  quitInstructionText.setPosition(getPlaceRight(escKeypadSprite, 50));
  avoidInstructionText.setPosition(getPlaceRight(airplaneSprite, 50));
  collectInstructionText.setPosition(getPlaceRight(CH4RefillerSprite, 50));
  continueText.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100);
}

void InstructionsScene::update(Game &game, sf::RenderWindow &window) { 
  if (sceneEvent.key.scancode == sf::Keyboard::Scan::Escape) {
    game.changeScene(new MenuScene(game, sceneFont));
  } else if (sceneEvent.key.scancode == sf::Keyboard::Scan::Enter) {
    game.changeScene(new PlayScene(window, sceneFont));
  }
  if(int(timer.getElapsedTime().asSeconds()*3)%2) {
    continueText.setString("");
  } else {
    continueText.setString("Press any key to continue...");
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

sf::Vector2f getCenter(sf::Sprite &sprite) {
  return {sprite.getTexture()->getSize().x / 2.0f, sprite.getTexture()->getSize().y / 2.0f};
}

sf::Vector2f getPlaceBelow(sf::Sprite &spriteOrigin, sf::Sprite &spriteToPlace, float gap) {
  return {spriteOrigin.getPosition().x, spriteOrigin.getPosition().y + (spriteOrigin.getTexture()->getSize().y / 2.0f) + (spriteToPlace.getTexture()->getSize().y / 2.0f) + gap};
}

sf::Vector2f getPlaceRight(sf::Sprite &spriteOrigin, sf::Sprite &spriteToPlace, float gap) {
  return {spriteOrigin.getPosition().x + (spriteOrigin.getTexture()->getSize().x / 2.0f) + (spriteToPlace.getTexture()->getSize().x / 2.0f) + gap, spriteOrigin.getPosition().y};
}

sf::Vector2f getPlaceRight(sf::Sprite &spriteOrigin, float gap) {
  return {spriteOrigin.getPosition().x + (spriteOrigin.getTexture()->getSize().x / 2.0f) + gap, spriteOrigin.getPosition().y};
}

InstructionsScene::~InstructionsScene() {}