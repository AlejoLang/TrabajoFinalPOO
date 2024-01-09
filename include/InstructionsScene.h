#pragma once 
#include <SFML/Graphics.hpp>

class InstructionsScene : public Scene {
  private:
    sf::Texture wKeypadTexture;
    sf::Texture arrowKeypadsTexture;
    sf::Texture escKeypadTexture;
    sf::Texture asteroidTexture;
    sf::Texture airplaneTexture;
    sf::Texture LOXRefillerTexture;
    sf::Texture CH4RefillerTexture;
    sf::Sprite wKeypadSprite;
    sf::Sprite arrowKeypadsSprite;
    sf::Sprite escKeypadSprite;
    sf::Sprite asteroidSprite;
    sf::Sprite airplaneSprite;
    sf::Sprite LOXRefillerSprite;
    sf::Sprite CH4RefillerSprite;
    sf::Text titleText;
    sf::Text accelerateInstructionText;
    sf::Text rotateInstructionText;
    sf::Text quitInstructionText;
    sf::Text avoidInstructionText;
    sf::Text collectInstructionText;
    sf::Text continueText;
    sf::Clock timer;
  public:
    InstructionsScene(sf::RenderWindow &window, sf::Font* gameFont);
    void setUpImages(sf::RenderWindow &window);
    void setUpText(sf::RenderWindow &window);
    void update(Game &game, sf::RenderWindow &window) override;
    void processEvent(sf::Event &ev) override;
    void drawIn(sf::RenderWindow &window) override;
    ~InstructionsScene();
};