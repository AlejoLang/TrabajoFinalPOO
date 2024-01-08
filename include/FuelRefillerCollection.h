#ifndef FUELREFILLERCOLLECTION
#define FUELREFILLERCOLLECTION
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class FuelRefiller;
class Ship;

class FuelRefillerCollection
{
  private:
    std::vector<FuelRefiller *> fuelRefillersVector;
    sf::Texture LOXRefillerTexture;
    sf::Texture CH4RefillerTexture;
    sf::Clock generationClock; 
    float generationTime;
    sf::SoundBuffer collectionSoundFile;
    sf::Sound collectionSound;
  public:
    FuelRefillerCollection(Game &game);
    void update(sf::View &mainView, Ship *playerShip, int gameDifficulty);
    void updateGenerationTime(int gameDifficulty);
    void handleRefillerGeneration(sf::View &mainView, Ship *playerShip);
    void handleRefillerCollision(Ship *playerShip);
    void handleRefillerRemove(sf::View &mainView);
    void drawIn(sf::RenderWindow &window);
    ~FuelRefillerCollection();
};


#endif