#ifndef SHIP_H
#define SHIP_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    float currentAltitudeKm;
    float maxAltitudeKm;
    float angularMomentum;
    sf::Texture animationTextures;
    sf::Sound explosionSound;
    sf::SoundBuffer explosionSoundFile;
    sf::Sound rocketSound;
    sf::SoundBuffer rocketSoundFile;
    Animation trustAnimation;
    AnimatedSprite trustAnimationSprite;
    Animation explosionAnimation;
    Animation* currentAnimation;
    AnimatedSprite explostionAnimationSprite;
    bool isAlive;
  public:
    Ship(sf::Texture &playerTexture, Map &mainMap);
    void update(Map &mainMap);
    void updateAltitude();
    void handleTrust();
    void handleRotation();
    void handleGravity(Map &mainMap);
    void handleTrustAnimation();
    void calculateDirection();
    void increaseLOX(float val);
    void increaseCH4(float val);
    void checkForDeath(Map &mainMap);
    float getLOX();
    float getCH4();
    float getAltitudeKm();
    float getVelocityKm_H();
    bool getStatus();
    bool isExplosionSoundPlaying();
    void drawIn(sf::RenderWindow &window) override;
    void explode();
    ~Ship() {};
};

#endif