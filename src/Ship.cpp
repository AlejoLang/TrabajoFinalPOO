#include <SFML/Graphics.hpp>
#include "Ship.h"
#include <math.h>
#include "Collision.h"
#include <iostream>

Ship::Ship (sf::Texture &playerTexture, Map &mainMap) 
    : Entity(playerTexture) 
    , trustAnimationSprite(sf::seconds(0.016), false, false)
    , explostionAnimationSprite(sf::seconds(0.016), false, false){
  entitySprite.setPosition({mainMap.getLaunchPadSprite().getPosition().x, mainMap.getLaunchPadSprite().getPosition().y - mainMap.getLaunchPadSprite().getGlobalBounds().height - entitySprite.getGlobalBounds().height / 2.0f + 1});
  std::cout<<"--------------"<<std::endl;
  std::cout<<entitySprite.getPosition().y<<std::endl;
  fuelLOX = 350;
  fuelCH4 = 100;
  acceleration = 0;
  gravityAcceleration = 0;
  velocity = {0, 0};
  isAlive = true;
  angularMomentum = 0;
  maxAltitudeKm = 0;
  currentAltitudeKm = 0;
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
}

void Ship::update(Map &mainMap) {
  if(!isAlive) {
    explostionAnimationSprite.update(sf::seconds(0.016));
  } else {
    handleTrust();
    calculateDirection();
    handleGravity(mainMap);
    entitySprite.move(velocity);
    handleTrustAnimation();
    updateAltitude();
    checkForDeath(mainMap);
  }
}

void Ship::updateAltitude() {
  currentAltitudeKm = -(entitySprite.getPosition().y / 2.0f) / 1000.0f;
  maxAltitudeKm = std::max(currentAltitudeKm, maxAltitudeKm);
}

void Ship::calculateDirection() {
  sf::Vector2f direction;
  direction.y = -1 * cos((entitySprite.getRotation()) * M_PI / 180);
  direction.x = 1 * sin((entitySprite.getRotation()) * M_PI / 180);
  velocity = {velocity.x * direction.x, velocity.y * direction.y};
}

void Ship::handleTrust() {
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuelLOX > 0 && fuelCH4 > 0) {
    fuelLOX -= 0.175;
    fuelCH4 -= 0.05;
    acceleration += 0.3;
    angularMomentum += velocity.x / acceleration * 0.25;
    trustAnimationSprite.play(trustAnimation);
  } else {
    acceleration -= 0.5;
    trustAnimationSprite.stop();
    trustAnimationSprite.setFrame(0);
  }
  angularMomentum += velocity.x / 30.0;
  acceleration = std::max(0.0f, std::min(acceleration, 40.0f));
  velocity -= {velocity.x - acceleration, velocity.y - acceleration};
}

void Ship::handleTrustAnimation() {
  float rotationAngle = entitySprite.getRotation() * M_PI / 180;
  float deltaX = -sin(rotationAngle) * (entitySprite.getTexture()->getSize().y / 2);
  float deltaY = cos(rotationAngle) * (entitySprite.getTexture()->getSize().y / 2);
  trustAnimationSprite.setPosition(entitySprite.getPosition().x + deltaX, entitySprite.getPosition().y + deltaY);
  trustAnimationSprite.setRotation(entitySprite.getRotation());
  trustAnimationSprite.update(sf::seconds(0.016));
}

void Ship::handleRotation() {
  const float maxRotationSpeed = 2.0;
    float rotationSpeed = angularMomentum / 10.0;
    
    rotationSpeed = std::min(rotationSpeed, maxRotationSpeed);
    rotationSpeed = std::max(rotationSpeed, -maxRotationSpeed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && fuelLOX > 0 && fuelCH4 > 0) {
        rotationSpeed -= 0.5;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && fuelLOX > 0 && fuelCH4 > 0) {
        rotationSpeed += 0.5;
    }

    entitySprite.rotate(rotationSpeed);
    angularMomentum *= 0.1;
}

void Ship::handleGravity(Map &mainMap) {
  if(!entitySprite.getGlobalBounds().intersects(mainMap.getGroundSprite().getGlobalBounds()) && !this->collides(mainMap.getLaunchPadSprite())){
    gravityAcceleration += 0.135;
    gravityAcceleration > 20 ? gravityAcceleration = 20 : gravityAcceleration = gravityAcceleration;
    velocity.y += gravityAcceleration;
    handleRotation();
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
  float velocity = std::sqrt(std::pow(this->velocity.x, 2) + std::pow(this->velocity.y, 2));
  velocity /= 0.016; /*Convert to pixels / seconds */
  velocity /= 2; /*Convert to m/s (1m = 2px)*/
  velocity *= 3.6; /*Convert to Km/h*/
  return velocity;
}

void Ship::drawIn(sf::RenderWindow &window) {
  if(!isAlive) {
    window.draw(explostionAnimationSprite);
  } else {
    window.draw(trustAnimationSprite);
    window.draw(entitySprite);
  }
}

void Ship::explode() {
  isAlive = false;
  explostionAnimationSprite.play(explosionAnimation);
  explostionAnimationSprite.setOrigin({120, 120});
  explostionAnimationSprite.setPosition(entitySprite.getPosition());
}

bool Ship::getStatus() {
  return this->isAlive;
}

void Ship::checkForDeath(Map &mainMap){
  if(entitySprite.getGlobalBounds().intersects(mainMap.getGroundSprite().getGlobalBounds())){
    this->explode();
  }
  if(maxAltitudeKm - currentAltitudeKm > 0.5) {
    this->explode();
  }
}