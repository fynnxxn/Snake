#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

const int TILE_SIZE = 32;
const int GRID_WIDTH = 17;
const int GRID_HEIGHT = 15;
const int SCORE_HEIGHT = 50;

class Game {
public:
    Game();
    void run();

private:
    void handleInput();
    void update();
    void render();
    void resetGame();

    sf::RenderWindow window;
    Snake snake;
    Food food;
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture foodTexture;
    sf::Sprite foodSprite;
    sf::Texture highScoreTexture;
    sf::Sprite highScoreSprite;
    sf::Text gameOverText;
    sf::RectangleShape restartButton;
    sf::Text restartText;
    sf::RectangleShape gameOverOverlay;
    sf::Sprite gameOverhighScoreSprite;
    sf::Sprite gameOverfoodSprite;
    sf::Text gameOverScoreText;
    sf::Text gameOverHighScoreText;
    sf::RectangleShape quitButton;
    sf::Text quitText;

    bool gameOver;
    bool gameStarted;
    int highScore = 0;
};


#endif
