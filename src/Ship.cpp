#include "Ship.h"
#include "Collision.h"
#define _USE_MATH_DEFINES /* Needed for using M_PI */
#include <math.h>

Ship::Ship (Game &game, sf::Texture &playerTexture, Map &mainMap) 
    : Entity(playerTexture) 
    , trustAnimationSprite(sf::seconds(0.016f), false, false)
    , explostionAnimationSprite(sf::seconds(0.016f), false, false)
{
  /* Set ship postion based on the launchpad */
  entitySprite.setPosition({mainMap.getLaunchPadSprite().getPosition().x, mainMap.getLaunchPadSprite().getPosition().y - mainMap.getLaunchPadSprite().getGlobalBounds().height - entitySprite.getGlobalBounds().height / 2.0f + 1});

  /* Set up animations */
  if(!animationTextures.loadFromFile("./resources/textures/playerTextures.png")) {exit(1);};
  trustAnimation.setSpriteSheet(animationTextures);
  for (int i = 0; i < 12; i++) {
    trustAnimation.addFrame(sf::IntRect(i * 240, 0, 240, 240));
  }
  explosionAnimation.setSpriteSheet(animationTextures);
  for (int i = 0; i < 12; i++) {
    explosionAnimation.addFrame(sf::IntRect(i * 240, 240, 240, 240));
  }
  trustAnimationSprite.setAnimation(trustAnimation);
  explostionAnimationSprite.setAnimation(explosionAnimation);
  trustAnimationSprite.setOrigin({120,120});

  /* Set up sounds */
  if(!explosionSoundFile.loadFromFile("./resources/sounds/explosion.wav")) { exit(1); }
  explosionSound.setBuffer(explosionSoundFile);
  explosionSound.setVolume(game.getGameVolume());
  explosionSound.setLoop(false);
  if(!rocketSoundFile.loadFromFile("./resources/sounds/rocket.wav")) { exit(1); }
  rocketSound.setBuffer(rocketSoundFile);
  rocketSound.setVolume(game.getGameVolume());
  rocketSound.setLoop(true);

  /* Set up variables */
  fuelLOX = 350;
  fuelCH4 = 100;
  acceleration = 0;
  gravityAcceleration = 0;
  velocity = { 0, 0 };
  isAlive = true;
  angularMomentum = 0;
  maxAltitudeKm = 0;
  currentAltitudeKm = 0;
}

void Ship::update(sf::RenderWindow& window, Map &mainMap) {
  if(!isAlive) {
    explostionAnimationSprite.update(sf::seconds(0.016f));
  } else {
    handleTrust(window);
    calculateDirection();
    handleGravity(window, mainMap);
    entitySprite.move(velocity);
    handleTrustAnimation();
    updateAltitude();
    checkForDeath(mainMap);
  }
}

void Ship::updateAltitude() {
  currentAltitudeKm = -(entitySprite.getPosition().y / 2.0f) / 1000.0f; /* Transform pixels to meters (1px = 2m) and then to Km*/
  maxAltitudeKm = std::max(currentAltitudeKm, maxAltitudeKm);
}

void Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * float(cos((entitySprite.getRotation()) * M_PI / 180.0f));
  direction.x = 1 * float(sin((entitySprite.getRotation()) * M_PI / 180.0f));
  velocity = {velocity.x * direction.x, velocity.y * direction.y};
}

void Ship::handleTrust(sf::RenderWindow& window) {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && window.hasFocus() && fuelLOX > 0 && fuelCH4 > 0) {
    /* Reduce fuel */
    fuelLOX -= 0.175f;
    fuelCH4 -= 0.05f;

    /* Increase velocity physics related variables*/
    acceleration += 0.3f;
    angularMomentum += velocity.x / acceleration * 0.25f;

    /* Play trust animation and sound */
    trustAnimationSprite.play(trustAnimation);
    if(rocketSound.getStatus() != sf::SoundSource::Status::Playing) {
      rocketSound.play();
    }
  } else {
    /* Decrease physic realted variables */
    acceleration -= 0.5;

    /* Stop trust animations and sounds*/
    trustAnimationSprite.stop();
    trustAnimationSprite.setFrame(0);
    rocketSound.pause();
  }

  /* Update physics realted variables */
  angularMomentum += velocity.x / 30.0f;
  acceleration = std::max(0.0f, std::min(acceleration, 40.f));
  velocity -= {velocity.x - acceleration, velocity.y - acceleration};
}

void Ship::handleTrustAnimation() {
  float rotationAngle = float(entitySprite.getRotation() * M_PI / 180.0f);
  /* Get the position of the back of the rocket */
  float deltaX = -sin(rotationAngle) * (entitySprite.getTexture()->getSize().y / 2.0f);
  float deltaY = cos(rotationAngle) * (entitySprite.getTexture()->getSize().y / 2.0f);
  /* Place the animation */
  trustAnimationSprite.setPosition(entitySprite.getPosition().x + deltaX, entitySprite.getPosition().y + deltaY);
  trustAnimationSprite.setRotation(entitySprite.getRotation());
  trustAnimationSprite.update(sf::seconds(0.016f));
}

void Ship::handleRotation(sf::RenderWindow& window) {
  const float maxRotationSpeed = 2.0;
  float rotationSpeed = angularMomentum / 10.0f;
  
  /* Cap rotation speed */
  rotationSpeed = std::min(rotationSpeed, maxRotationSpeed);
  rotationSpeed = std::max(rotationSpeed, -maxRotationSpeed);

  /* change rotation speed when arrow keys are pressed */
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && window.hasFocus() && fuelLOX > 0 && fuelCH4 > 0) {
    rotationSpeed -= 0.5;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && window.hasFocus() && fuelLOX > 0 && fuelCH4 > 0) {
    rotationSpeed += 0.5;
  }

  entitySprite.rotate(rotationSpeed);
  angularMomentum *= 0.1f;
}

void Ship::handleGravity(sf::RenderWindow& window, Map &mainMap) {
  /* Apply gravity when the player isnt touching the ground or the lauchpad */
  if(!entitySprite.getGlobalBounds().intersects(mainMap.getGroundSprite().getGlobalBounds()) && !this->collides(mainMap.getLaunchPadSprite())){
    gravityAcceleration += 0.135f;
    gravityAcceleration > 20.0f ? gravityAcceleration = 20.0f : gravityAcceleration = gravityAcceleration;
    velocity.y += gravityAcceleration;
    handleRotation(window);
  } else {
    gravityAcceleration = 0;
    acceleration = 0;
  }
}

void Ship::increaseCH4(float val) {
  this->fuelCH4 += val;
  if(fuelCH4 > 100) {fuelCH4 = 100;}
}

void Ship::increaseLOX(float val) {
  this->fuelLOX += val;
  if(fuelLOX > 350) {fuelLOX = 350;}
}

float Ship::getCH4() {
  return this->fuelCH4;
}

float Ship::getLOX() {
  return this->fuelLOX;
}

float Ship::getAltitudeKm() {
  return this->currentAltitudeKm;
}

float Ship::getVelocityKm_H() {
  float velocity = float(std::sqrt(std::pow(this->velocity.x, 2) + std::pow(this->velocity.y, 2)));
  velocity /= 0.016f; /*Convert to pixels / seconds */
  velocity /= 2.0f; /*Convert to m/s (1m = 2px)*/
  velocity *= 3.6f; /*Convert to Km/h*/
  return velocity;
}

bool Ship::isExplosionSoundPlaying() {
  return explosionSound.getStatus() == sf::SoundSource::Status::Playing;
}

void Ship::explode() {
  /* Execute the funciton only once */
  if (!isAlive) { return; }
  isAlive = false;

  /* stop trust sound */
  rocketSound.stop();

  /* Start explosion sound and animation*/
  if (explosionSound.getStatus() == sf::SoundSource::Status::Stopped) {
    explosionSound.play();
  }
  explostionAnimationSprite.play(explosionAnimation);
  explostionAnimationSprite.setOrigin({ 120, 120 });
  explostionAnimationSprite.setPosition(entitySprite.getPosition());
}

bool Ship::getStatus() {
  return this->isAlive;
}

void Ship::checkForDeath(Map& mainMap) {
  if (entitySprite.getGlobalBounds().intersects(mainMap.getGroundSprite().getGlobalBounds())) {
    this->explode();
  }
  if (maxAltitudeKm - currentAltitudeKm > 0.5) {
    this->explode();
  }
}

void Ship::drawIn(sf::RenderWindow &window) {
  if(!isAlive) {
    window.draw(explostionAnimationSprite);
  } else {
    window.draw(trustAnimationSprite);
    window.draw(entitySprite);
  }
}