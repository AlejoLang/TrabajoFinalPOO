#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Entity.h"
#include "AnimatedSprite.h"
#include "Map.h"

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
    AnimatedSprite explostionAnimationSprite;
    bool isAlive;
  public:
    Ship(Game &game, sf::Texture &playerTexture, Map &mainMap);
    void update(sf::RenderWindow& window, Map &mainMap);
    void updateAltitude();
    void handleTrust(sf::RenderWindow& window);
    void handleRotation(sf::RenderWindow& window);
    void handleGravity(sf::RenderWindow& window, Map &mainMap);
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