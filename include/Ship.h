#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map.h"
#include "Asteroid.h"
#include "AnimatedSprite.h"

class Ship : public Entity {
  private:
    sf::Vector2f velocity;
    float acceleration;
    float gravityAcceleration;
    float fuelLOX;
    float fuelCH4;
    float altitudeKm;
    float angularMomentum;
    sf::Texture animationTextures;
    Animation trustAnimation;
    AnimatedSprite trustAnimationSprite;
    Animation explosionAnimation;
    Animation* currentAnimation;
    AnimatedSprite explostionAnimationSprite;
  public:
    Ship(sf::Texture &playerTexture, Map &mainMap, sf::RenderWindow &window);
    void update(Map &mainMap);
    void updateAltitude();
    void handleTrust();
    void handleRotation();
    void handleGravity(Map &mainMap);
    void handleTrustAnimation();
    void calculateDirection();
    void increaseLOX(float val);
    void increaseCH4(float val);
    float getLOX();
    float getCH4();
    float getAltitude();
    void drawIn(sf::RenderWindow &window) override;
};

#endif